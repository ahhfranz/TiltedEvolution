#include <Structs/AnimationGraphDescriptorManager.h>
#include <Structs/Fallout4/AnimationGraphDescriptor_Deer.h>

enum Variables
{
    kiState = 0,
    kiState_RadStag = 1,
    kbGraphDriven = 2,
    kbGraphDrivenRotation = 3,
    kbGraphDrivenTranslation = 4,
    kbAnimationDriven = 5,
    kbAllowRotation = 6,
    kstaggerDirection = 7,
    kstaggerMagnitude = 8,
    kiGetUpType = 9,
    kiCombatState = 10,
    kcHitReactionBodyPart = 11,
    kbManualGraphChange = 12,
    kbSupportedDeathAnim = 13,
    kfTimeStep = 14,
    kLHeadTwistGainAdj = 15,
    kLHeadTwistGain = 16,
    kLHeadXTwist = 17,
    kLHeadValueMinMax = 18,
    kLHeadYTwist = 19,
    kLHeadZTwist = 20,
    kfRHeadTwistGainAdj = 21,
    kfRHeadTwistGain = 22,
    kRHeadXTwist = 23,
    kRHeadValueMinMax = 24,
    kRHeadYTwist = 25,
    kRHeadZTwist = 26,
    kSpineXTwist = 27,
    kSpineYTwist = 28,
    kSpineZTwist = 29,
    kfSpineTwistGain = 30,
    kfSpineTwistGainAdj = 31,
    kSpineValueMinMax = 32,
    kbReactEnabled = 33,
    kfHitReactionEndTimer = 34,
    kiSyncTurnState = 35,
    kiNonCombatStandingState = 36,
    kiNonCombatLocomotionState = 37,
    kiSyncIdleLocomotion = 38,
    kSpeed = 39,
    kiCombatStandingState = 40,
    kiCombatLocomotionState = 41,
    kIsAttackReady = 42,
    kbEnableAttackMod = 43,
    kbEquipOk = 44,
    kfRandomClipStartTimePercentage = 45,
    kbIsSynced = 46,
    kcHitReactionDir = 47,
    kTurnDeltaSmoothed = 48,
    kidleTimeMax = 49,
    kidleTimeMin = 50,
    kbHeadTrackingEnable = 51,
    kbGraphWantsHeadTracking_Left = 52,
    kfHeadTrackingGainOn = 53,
    kfHeadTrackingGainOff = 54,
    kcamerafromx = 55,
    kcamerafromy = 56,
    kcamerafromz = 57,
    k_LimitAngleRight = 58,
    k_LimitAngleUp = 59,
    k_LimitAngleDown = 60,
    k_LimitAngleLeft = 61,
    k_LimitAngleLeft00 = 62,
    k_LimitAngle = 63,
    kLookAtOutOfRange = 64,
    kLookAtOutOfRange2 = 65,
    kbHeadTrackingDebug = 66,
    krightHeadVector = 67,
    krightHeadUpVector = 68,
    kleftHeadVector = 69,
    kleftHeadUpVector = 70,
    kiDynamicAnimSelector = 71,
    kiSyncForwardState = 72,
    kDirection = 73,
    kbGraphWantsHeadTracking_Right = 74,
    kIsSprinting = 75,
    kiSyncSprintState = 76,
    kbAllowHeadTracking = 77,
    kLookAtChest_Enabled = 78,
    kLookAtSpine2_Enabled = 79,
    kbFreezeSpeedUpdate = 80,
    kiIsInSneak = 81,
    kbGraphWantsFootIK = 82,
    kbRenderFirstPersonInWorld = 83,
    kbDisableSpineTracking = 84,
    kIsPlayer = 85,
    kbBlockPOVSwitch = 86,
    kbBlockPipboy = 87,
    kPose = 88,
    kbAdjust1stPersonFOV = 89,
    kiRecoilSelector = 90,
    kTurnDelta = 91,
    kIsBlocking = 92,
    kiSyncWalkRun = 93,
    krecoilShortMult = 94,
    kLookAtOutsideLimit = 95,
    kbForceIdleStop = 96,
    kbDoNotInterrupt = 97,
    kLookAtLimitAngleDeg = 98,
    kLookAtChest_LimitAngleDeg = 99,
    kLookAtNeck_LimitAngleDeg = 100,
    kLookAtHead_LimitAngleDeg = 101,
    kLookAtHead_OnGain = 102,
    kLookAtAdditive = 103,
    kbEnableRoot_IsActiveMod = 104,
    kIsNPC = 105,
    kLookAtOnGain = 106,
    kLookAtOffGain = 107,
    kbTalkableWithItem = 108,
    kiTalkGenerator = 109,
    kbFreezeRotationUpdate = 110,
    kiPcapTalkGenerator = 111,
    kSpeedSmoothed = 112,
    kbIsInFlavor = 113,
};

AnimationGraphDescriptor_Deer::AnimationGraphDescriptor_Deer(
    AnimationGraphDescriptorManager& aManager)
{
    size_t key = 802028733968326397;

    AnimationGraphDescriptorManager::Builder s_builder(aManager, key,
        AnimationGraphDescriptor(
            {
                kIsSprinting,
                kbEquipOk,
                kbGraphWantsHeadTracking_Right,
                kbGraphWantsHeadTracking_Left,
                kIsAttackReady,
            },
            {
                kTurnDelta,
                kSpeed,
                kTurnDeltaSmoothed,
                kSpeedSmoothed,
                kDirection,
            },
            {
                kiCombatState,
                kiSyncTurnState,
                kiSyncIdleLocomotion,
                kiSyncSprintState,
            }
        ));
}
