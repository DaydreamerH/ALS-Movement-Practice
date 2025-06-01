// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/CharacterInterfaces.h"
#include "LyraAnimInstance.generated.h"

enum class ELocomotionDirection : uint8;
enum class ECharacterGate : uint8;
class ICharacterInterface;
enum class EGuns : uint8;
class ALyraCharacter;
/**
 * 
 */
UCLASS()
class LYRA_API ULyraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void UpdateLayerData();

	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	APawn* PawnOwner = nullptr;
	
	/** 角色信息 **/
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FVector2D HorizontalVelocity = FVector2D::ZeroVector;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ECharacterGate CharacterCurrentGate;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ECharacterGate CharacterLastGate;
	void UpdateCharacterGate();
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float VelocityLocomotionAngle = 0.f;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ELocomotionDirection VelocityLocomotionDirection = ELocomotionDirection::ELD_Forward;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ELocomotionDirection LastVelocityLocomotionDirection;
	void UpdateLocomotionDirection(float Angle, ELocomotionDirection& Direction);
	const float ForwardMinBound = -50.f;
	const float ForwardMaxBound = 50.f;
	const float BackwardMinBound = -130.f;
	const float BackwardMaxBound = 130.f;
	const float DeadZone = 10.f;

	float LastCharacterYaw = 0.f;
	float CurrentCharacterYaw = 0.f;
	void CalculateLeanAngle(float DeltaSeconds);
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float LeanAngle = 0.f;
	float DeltaYaw = 0.f;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsCharacterAccelerating = false;

	void GetCharacterStopDistance();
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float StopDistance = 0.f;

	void GetCharacterMaxWalkSpeed();
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float CharacterMaxWalkSpeed = 0.f;

	FVector CharacterCurrentLocation = FVector::ZeroVector;
	FVector CharacterLastLocation = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float CharacterDeltaLocation;
	void CalculateDeltaLocation();

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FVector2D HorizontalAcceleration = FVector2D::ZeroVector;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	FVector2D PivotHorizontalAcceleration = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ELocomotionDirection AccelerationLocomotionDirection = ELocomotionDirection::ELD_Forward;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float AccelerationLocomotionAngle = 0.f;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float PivotDistance = 0.f;
	void GetCharacterPivotDistance();

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float RootYawOffset = 0.f;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	ERootYawOffsetMode RootYawOffsetMode = ERootYawOffsetMode::ERYOM_Accumulate;
	void UpdateRootYawOffset(float DeltaTime);
	float TargetRootYawOffset = 0.0f;
	float RootYawOffsetVelocity = 0.0f;
	float SpringStiffness = 30.0f;
	float SpringDampingFactor = 1.0f;
	float SpringMass = 1.0f;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float VelocityLocomotionAngleWithOffset = 0.f;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bShouldTurnLeft = false;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsCrouching = false;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bLastFrameIsCrouching = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	bool bCrouchStateChanged = false;
};
