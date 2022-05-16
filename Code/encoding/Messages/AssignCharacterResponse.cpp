#include <Messages/AssignCharacterResponse.h>

void AssignCharacterResponse::SerializeRaw(TiltedPhoques::Buffer::Writer& aWriter) const noexcept
{
    Serialization::WriteBool(aWriter, Owner);
    Serialization::WriteVarInt(aWriter, Cookie);
    Serialization::WriteVarInt(aWriter, ServerId);
    Position.Serialize(aWriter);
    CellId.Serialize(aWriter);
    WorldSpaceId.Serialize(aWriter);
    AllActorValues.Serialize(aWriter);
    Serialization::WriteBool(aWriter, IsDead);
    Serialization::WriteBool(aWriter, IsWeaponDrawn);
}

void AssignCharacterResponse::DeserializeRaw(TiltedPhoques::Buffer::Reader& aReader) noexcept
{
    Owner = Serialization::ReadBool(aReader);
    Cookie = Serialization::ReadVarInt(aReader) & 0xFFFFFFFF;
    ServerId = Serialization::ReadVarInt(aReader) & 0xFFFFFFFF;
    Position.Deserialize(aReader);
    CellId.Deserialize(aReader);
    WorldSpaceId.Deserialize(aReader);
    AllActorValues.Deserialize(aReader);
    IsDead = Serialization::ReadBool(aReader);
    IsWeaponDrawn = Serialization::ReadBool(aReader);
}
