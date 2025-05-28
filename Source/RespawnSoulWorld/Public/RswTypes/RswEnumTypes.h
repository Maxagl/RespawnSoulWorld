#pragma once

UENUM()
enum class ERswConfirmType : uint8
{
    Yes,
    No
};

UENUM()
enum class ERswValidType : uint8
{
    Valid,
    Invalid
};

UENUM()
enum class ERswSuccessType : uint8
{
    Successful,
    Failed
};

UENUM()
enum class ERswCountDownActionInput : uint8
{
    Start,
    Cancel
};

UENUM()
enum class ERswCountDownActionOutput : uint8
{
    Updated,
    Completed,
    Cancelled
};

UENUM(BlueprintType)
enum class ERswGameDifficulty : uint8
{
    Easy,
    Normal,
    Hard,
    VeryHard
};