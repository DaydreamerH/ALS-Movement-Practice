// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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
	UPROPERTY()
	APawn* PawnOwner = nullptr;
	
	/** 角色信息 **/
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FVector2D HorizontalVelocity = FVector2D::ZeroVector;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ECharacterGate CharacterCurrentGate;
	
	float VelocityLocomotionAngle = 0.f;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ELocomotionDirection VelocityLocomotionDirection;
	void UpdateVelocityLocomotionDirection();
	const float ForwardMinBound = -50.f;
	const float ForwardMaxBound = 50.f;
	const float BackwardMinBound = -130.f;
	const float BackwardMaxBound = 130.f;
	const float DeadZone = 20.f;
};
