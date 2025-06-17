#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LayerInterface.generated.h"

enum class ECharacterGate : uint8;

UINTERFACE(BlueprintType)
class LYRA_API ULayerInterface : public UInterface
{
	GENERATED_BODY()
};

class LYRA_API ILayerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetDirection(ELocomotionDirection Direction);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCharacterCurrentGate(ECharacterGate CharacterGate);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetIsCrouching(bool bCrouch);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetStopDistance(float Distance);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCharacterDeltaLocation(float Location);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetPivotDistance(float Distance);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetHorizontalVelocity(FVector2D HorizontalVelocity);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetHorizontalAcceleration(FVector2D HorizontalAcceleration);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetRootYawOffset(float Offset);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetShouldTurnLeft(bool Left);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetAccelerationLocomotionDirection(ELocomotionDirection Direction);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCrouchStateChanged(bool Change);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetAccelerationLocomotionAngle(float Angle);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetLeanAngle(float Angle);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetVelocityLocomotionAngle(float Angle);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetVelocityLocomotionAngleWithOffset(float Angle);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetGroundDistance(float GD);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetIsInAir(bool Air);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetFallingTime(float FallingTime);
};