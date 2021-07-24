#include <Structs/AnimationGraphDescriptorManager.h>
#include <Structs/Fallout4/AnimationGraphDescriptor_Gorilla.h>

enum Variables
{
    kiState = 0,
    kiState_Gorilla = 1,
    kbGraphDriven = 2,
    kbGraphDrivenRotation = 3,
    kbGraphDrivenTranslation = 4,
    kbAnimationDriven = 5,
    kbAllowRotation = 6,
    kstaggerDirection = 7,
    kstaggerMagnitude = 8,
    kiGetUpType = 9,
    kiCombatState = 10,
    kbHeadTrackingEnabled = 11,
    kbGraphWantsHeadTracking = 12,
    kLookAtOutOfRange = 13,
    kcamerafromx = 14,
    kcamerafromy = 15,
    kcamerafromz = 16,
    kbHeadTrackingDebug = 17,
    kfTimeStep = 18,
    kfSpineTwistGainAdj = 19,
    kfSpineTwistGain = 20,
    kSpineXTwist = 21,
    kSpineYTwist = 22,
    kSpineZTwist = 23,
    kfHeadTwistGainAdj = 24,
    kfHeadTwistGain = 25,
    kHeadXTwist = 26,
    kHeadYTwist = 27,
    kHeadZTwist = 28,
    kbManualGraphChange = 29,
    kcHitReactionBodyPart = 30,
    kfHitReactionEndTimer = 31,
    kiSyncTurnState = 32,
    kiNonCombatStandingState = 33,
    kiNonCombatLocomotionState = 34,
    kiSyncIdleLocomotion = 35,
    kSpeed = 36,
    kiCombatStandingState = 37,
    kiCombatLocomotionState = 38,
    kIsAttackReady = 39,
    kbEnableAttackMod = 40,
    kbEquipOk = 41,
    kfRandomClipStartTimePercentage = 42,
    kidleTimeMin = 43,
    kidleTimeMax = 44,
    kiDynamicAnimSelector = 45,
    kfLocomotionRunMult = 46,
    kfLocomotionWalkMult = 47,
    kDirection = 48,
    kbAllowHeadTracking = 49,
    kLookAtChest_Enabled = 50,
    kLookAtSpine2_Enabled = 51,
    kbFreezeSpeedUpdate = 52,
    kiIsInSneak = 53,
    kbGraphWantsFootIK = 54,
    kbRenderFirstPersonInWorld = 55,
    kbDisableSpineTracking = 56,
    kIsPlayer = 57,
    kbBlockPOVSwitch = 58,
    kbBlockPipboy = 59,
    kPose = 60,
    kbAdjust1stPersonFOV = 61,
    kiRecoilSelector = 62,
    kTurnDelta = 63,
    kIsBlocking = 64,
    kiSyncWalkRun = 65,
    krecoilShortMult = 66,
    kLookAtOutsideLimit = 67,
    kbForceIdleStop = 68,
    kbDoNotInterrupt = 69,
    kLookAtLimitAngleDeg = 70,
    kLookAtChest_LimitAngleDeg = 71,
    kLookAtNeck_LimitAngleDeg = 72,
    kLookAtHead_LimitAngleDeg = 73,
    kLookAtHead_OnGain = 74,
    kLookAtAdditive = 75,
    kbEnableRoot_IsActiveMod = 76,
    kIsNPC = 77,
    kLookAtOnGain = 78,
    kLookAtOffGain = 79,
    kbTalkableWithItem = 80,
    kiTalkGenerator = 81,
    kbFreezeRotationUpdate = 82,
    kiPcapTalkGenerator = 83,
    kSpeedSmoothed = 84,
    kTurnDeltaSmoothed = 85,
    kbIsInFlavor = 86,
};

AnimationGraphDescriptor_Gorilla::AnimationGraphDescriptor_Gorilla(
    AnimationGraphDescriptorManager& aManager)
{
    size_t key = 6300528841859302718;

    AnimationGraphDescriptorManager::Builder s_builder(aManager, key,
        AnimationGraphDescriptor(
            {
                kbEquipOk,
                kbAnimationDriven,
                kIsAttackReady,
                kLookAtOutOfRange,
                kbGraphWantsHeadTracking,
            },
            {
                kSpeedSmoothed,
                kstaggerDirection,
                kfHeadTwistGainAdj,
                kSpeed,
                kSpineZTwist,
                kfSpineTwistGainAdj,
                kfHitReactionEndTimer,
                kSpineYTwist,
                kDirection,
                kfTimeStep,
                kfLocomotionWalkMult,
                kTurnDeltaSmoothed,
                kSpineXTwist,
                kTurnDelta,
                kfLocomotionRunMult,
            },
            {
                kiRecoilSelector,
                kiSyncTurnState,
                kiCombatState,
                kiSyncIdleLocomotion,
                kcHitReactionBodyPart,
            }
        ));
}
