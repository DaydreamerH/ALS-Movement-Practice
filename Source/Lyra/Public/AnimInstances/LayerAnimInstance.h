// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LayerInterface.h"
#include "Animation/AnimInstance.h"
#include "LayerAnimInstance.generated.h"


enum class ECharacterGate : uint8;
enum class ELocomotionDirection : uint8;

UCLASS()
class LYRA_API ULayerAnimInstance : public UAnimInstance, public ILayerInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	ELocomotionDirection VelocityLocomotionDirection;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	ECharacterGate CharacterCurrentGate;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bIsCrouching = false;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	FVector2D HorizontalAcceleration;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	FVector2D HorizontalVelocity;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float PivotDistance;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float StopDistance;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float CharacterDeltaLocation;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float RootYawOffset;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bShouldTurnLeft;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	ELocomotionDirection AccelerationLocomotionDirection;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bCrouchStateChanged;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float LeanAngle;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float AccelerationLocomotionAngle;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float VelocityLocomotionAngle;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float VelocityLocomotionAngleWithOffset;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float GroundDistance;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float FallingTime = 0.f;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float Pitch = 0.f;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	FVector2D PivotHorizontalAcceleration;
public:
	virtual void SetDirection_Implementation(ELocomotionDirection Direction) override;
	virtual void SetCharacterCurrentGate_Implementation(ECharacterGate Gate) override;
	virtual void SetHorizontalAcceleration_Implementation(FVector2D Acceleration) override;
	virtual void SetHorizontalVelocity_Implementation(FVector2D Velocity) override;
	virtual void SetIsCrouching_Implementation(bool bCrouch) override;
	virtual void SetPivotDistance_Implementation(float Distance) override;
	virtual void SetStopDistance_Implementation(float Distance) override;
	virtual void SetCharacterDeltaLocation_Implementation(float Location) override;
	virtual void SetRootYawOffset_Implementation(float Offset) override;
	virtual void SetShouldTurnLeft_Implementation(bool Left) override;
	virtual void SetAccelerationLocomotionDirection_Implementation(ELocomotionDirection Direction) override;
	virtual void SetCrouchStateChanged_Implementation(bool Change) override;
	virtual void SetLeanAngle_Implementation(float Angle) override;
	virtual void SetAccelerationLocomotionAngle_Implementation(float Angle) override;
	virtual void SetVelocityLocomotionAngle_Implementation(float Angle) override;
	virtual void SetVelocityLocomotionAngleWithOffset_Implementation(float Angle) override;
	virtual void SetGroundDistance_Implementation(float GD) override;
	virtual void SetIsInAir_Implementation(bool Air) override;
	virtual void SetFallingTime_Implementation(float fallingTime) override;
	virtual void SetPitch_Implementation(float Pitch) override;
};
