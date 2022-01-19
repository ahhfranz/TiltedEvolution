/*
 * This file is part of the CitizenFX project - http://citizen.re/
 *
 * See LICENSE and MENTIONS in the root of the source tree for information
 * regarding licensing.
 */

// Changes:
// - 2021/2/24: Moved TLS routine.
// - 2021/2/25: Implemented CEG decryption method.

#include "ExeLoader.h"
#include "steam/SteamCeg.h"
#include <TiltedCore/Filesystem.hpp>

#include "steam/SteamCeg.h"

ExeLoader::ExeLoader(uint32_t aLoadLimit, TFuncHandler aFuncHandler)
    : 
    m_loadLimit(aLoadLimit), m_pFuncHandler(aFuncHandler)
{}

void ExeLoader::LoadImports(const IMAGE_NT_HEADERS* apNtHeader)
{
    const auto* importDirectory = &apNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    const auto* descriptor = GetTargetRVA<const IMAGE_IMPORT_DESCRIPTOR>(importDirectory->VirtualAddress);

    while (descriptor->Name)
    {
        const char* name = GetTargetRVA<char>(descriptor->Name);

        HMODULE module = LoadLibraryA(name);
        if (!module)
        {
            __debugbreak();
            continue;
        }

        // "don't load"
        if (*reinterpret_cast<uint32_t*>(module) == 0xFFFFFFFF)
        {
            descriptor++;
            continue;
        }

        auto nameTableEntry = GetTargetRVA<uintptr_t>(descriptor->OriginalFirstThunk);
        auto addressTableEntry = GetTargetRVA<uintptr_t>(descriptor->FirstThunk);

        if (!descriptor->OriginalFirstThunk)
        {
            nameTableEntry = GetTargetRVA<uintptr_t>(descriptor->FirstThunk);
        }

        while (*nameTableEntry)
        {
            FARPROC function;
            const char* functionName;

            // is this an ordinal-only import?
            if (IMAGE_SNAP_BY_ORDINAL(*nameTableEntry))
            {
                function = GetProcAddress(module, MAKEINTRESOURCEA(IMAGE_ORDINAL(*nameTableEntry)));
            }
            else
            {
                auto import = GetTargetRVA<IMAGE_IMPORT_BY_NAME>(static_cast<uint32_t>(*nameTableEntry));

                function = m_pFuncHandler(module, import->Name);
                functionName = import->Name;
            }

            if (!function)
            {
                char pathName[MAX_PATH];
                GetModuleFileNameA(module, pathName, sizeof(pathName));
            }

            *addressTableEntry = (uintptr_t)function;

            nameTableEntry++;
            addressTableEntry++;
        }

        descriptor++;
    }
}

void ExeLoader::LoadSections(const IMAGE_NT_HEADERS* apNtHeader)
{
    auto* section = IMAGE_FIRST_SECTION(apNtHeader);
    for (int i = 0; i < apNtHeader->FileHeader.NumberOfSections; i++)
    {
        uint8_t* targetAddress = GetTargetRVA<uint8_t>(section->VirtualAddress);
        const void* sourceAddress = m_pBinary + section->PointerToRawData;

        if (targetAddress >= (reinterpret_cast<uint8_t*>(m_moduleHandle) + m_loadLimit))
        {
            return;
        }

        if (section->SizeOfRawData > 0)
        {
            uint32_t sizeOfData = std::min(section->SizeOfRawData, section->Misc.VirtualSize);

            memcpy(targetAddress, sourceAddress, sizeOfData);

            DWORD oldProtect;
            VirtualProtect(targetAddress, sizeOfData, PAGE_EXECUTE_READWRITE, &oldProtect);
        }

        section++;
    }
}

void ExeLoader::LoadTLS(const IMAGE_NT_HEADERS* apNtHeader, const IMAGE_NT_HEADERS* apSourceNt)
{
    if (apNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size)
    {
        const auto* sourceTls = GetTargetRVA<IMAGE_TLS_DIRECTORY>(
            apNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
        const auto* targetTls = GetTargetRVA<IMAGE_TLS_DIRECTORY>(
            apSourceNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);

        *(DWORD*)(sourceTls->AddressOfIndex) = 0;

        LPVOID tlsBase = *(LPVOID*)__readgsqword(0x58);

        DWORD oldProtect;
        VirtualProtect(reinterpret_cast<LPVOID>(targetTls->StartAddressOfRawData),
                       sourceTls->EndAddressOfRawData - sourceTls->StartAddressOfRawData, PAGE_READWRITE, &oldProtect);

        std::memcpy(tlsBase, reinterpret_cast<void*>(sourceTls->StartAddressOfRawData),
               sourceTls->EndAddressOfRawData - sourceTls->StartAddressOfRawData);
        std::memcpy((void*)targetTls->StartAddressOfRawData, reinterpret_cast<void*>(sourceTls->StartAddressOfRawData),
               sourceTls->EndAddressOfRawData - sourceTls->StartAddressOfRawData);
    }
}

uint32_t ExeLoader::Rva2Offset(uint32_t aRva) noexcept
{
    const auto* dos = GetRVA<const IMAGE_DOS_HEADER>(0);
    const auto* nt = GetRVA<const IMAGE_NT_HEADERS>(dos->e_lfanew);

    auto* section = IMAGE_FIRST_SECTION(nt);
    for (int i = 0; i < nt->FileHeader.NumberOfSections; i++)
    {
        if (aRva >= section[i].VirtualAddress && (aRva < section[i].VirtualAddress + section[i].Misc.VirtualSize))
        {
            return static_cast<uint32_t>(aRva - (section[i].VirtualAddress - section[i].PointerToRawData));
        }
    }

    return 0;
}

void ExeLoader::DecryptCeg(IMAGE_NT_HEADERS* apSourceNt)
{
    auto entry = apSourceNt->OptionalHeader.AddressOfEntryPoint;
    // analyze executable sections if the entry point is already protected
    if (*GetOffset<uint32_t>(entry) != 0x000000e8)
        return;

    const auto* section = IMAGE_FIRST_SECTION(apSourceNt);
    for (int i = 0; i < apSourceNt->FileHeader.NumberOfSections; i++)
    {
        if (!_strcmpi(reinterpret_cast<const char*>(section[i].Name), ".text"))
        {
            break;
        }
    }

    steam::CEGLocationInfo info{GetOffset<uint8_t>(entry),
                                {GetOffset<uint8_t>(section->VirtualAddress), section->SizeOfRawData}};

    auto realEntry = steam::CrackCEGInPlace(info);

    apSourceNt->FileHeader.NumberOfSections--;
    apSourceNt->OptionalHeader.AddressOfEntryPoint = static_cast<uint32_t>(realEntry);
}

bool ExeLoader::Load(const uint8_t* apProgramBuffer)
{
    m_pBinary = apProgramBuffer;
    m_moduleHandle = GetModuleHandleW(nullptr);

    // validate the target
    const auto* dosHeader = GetRVA<const IMAGE_DOS_HEADER>(0);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        return false;
    }

    // remove protections
    auto* ntHeader = GetRVA<IMAGE_NT_HEADERS>(dosHeader->e_lfanew);
    DecryptCeg(ntHeader);

    // these point to launcher.exe's headers
    auto* sourceHeader = GetTargetRVA<IMAGE_DOS_HEADER>(0);
    auto* sourceNtHeader = GetTargetRVA<IMAGE_NT_HEADERS>(sourceHeader->e_lfanew);

    // store EP
    m_pEntryPoint = GetTargetRVA<void>(ntHeader->OptionalHeader.AddressOfEntryPoint);

    // store these as they will get overridden by the target's header
    // but we really need them in order to not break debugging for cosi.
    auto sourceChecksum= sourceNtHeader->OptionalHeader.CheckSum;
    auto sourceTimestamp = sourceNtHeader->FileHeader.TimeDateStamp;
    auto sourceDebugDir = sourceNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG];

    LoadSections(ntHeader);
    LoadImports(ntHeader);
    LoadTLS(ntHeader, sourceNtHeader);

    // copy over the offset to the new imports directory
    DWORD oldProtect;
    VirtualProtect(sourceNtHeader, 0x1000, PAGE_EXECUTE_READWRITE, &oldProtect);

    // re-target the import directory to the target's; ours isn't needed anymore.
    sourceNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT] =
        ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

    const size_t ntCompleteHeaderSize =
        sizeof(IMAGE_NT_HEADERS) + (ntHeader->FileHeader.NumberOfSections * (sizeof(IMAGE_SECTION_HEADER)));

    // overwrite our headers with the target headers
    std::memcpy(sourceNtHeader, ntHeader, ntCompleteHeaderSize);

    // good old switcheroo
    // TODO: consider making this optional to allow loading the game's pdb.
    sourceNtHeader->OptionalHeader.CheckSum = sourceChecksum;
    sourceNtHeader->FileHeader.TimeDateStamp = sourceTimestamp;
    sourceNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG] = sourceDebugDir;

    m_pBinary = nullptr;
    return true;
}
