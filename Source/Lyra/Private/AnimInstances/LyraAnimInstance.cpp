// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/LyraAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Characters/LyraCharacter.h"

void ULyraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	PawnOwner = TryGetPawnOwner();
}

void ULyraAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	PawnOwner = PawnOwner == nullptr ? TryGetPawnOwner() : PawnOwner;
	if(PawnOwner && PawnOwner->Implements<UCharacterInterface>())
	{
		FRotator CharacterRotation = ICharacterInterface::Execute_GetCharacterRotation(PawnOwner);
		
		HorizontalVelocity = ICharacterInterface::Execute_GetCharacterHorizontalVelocity(PawnOwner);

		UpdateCharacterGate();
		
		
		VelocityLocomotionAngle = UKismetAnimationLibrary::CalculateDirection({HorizontalVelocity.X, HorizontalVelocity.Y,0.f}, CharacterRotation);
		LastVelocityLocomotionDirection = VelocityLocomotionDirection;
		UpdateLocomotionDirection(VelocityLocomotionAngle, VelocityLocomotionDirection);

		LastCharacterYaw = CurrentCharacterYaw;
		CurrentCharacterYaw = CharacterRotation.Yaw;
		CalculateLeanAngle(DeltaSeconds);

		bIsCharacterAccelerating = ICharacterInterface::Execute_IsCharacterAccelerating(PawnOwner);
		
		GetCharacterStopDistance();

		GetCharacterMaxWalkSpeed();

		CharacterLastLocation = CharacterCurrentLocation;
		CharacterCurrentLocation = ICharacterInterface::Execute_GetCharacterLocation(PawnOwner);
		CalculateDeltaLocation();

		HorizontalAcceleration = ICharacterInterface::Execute_GetCharacterHorizontalAcceleration(PawnOwner);
		AccelerationLocomotionAngle = UKismetAnimationLibrary::CalculateDirection({HorizontalAcceleration.X, HorizontalAcceleration.Y,0.f}, CharacterRotation);
		UpdateLocomotionDirection(AccelerationLocomotionAngle, AccelerationLocomotionDirection);

		GetCharacterPivotDistance();

		
		UpdateRootYawOffset(DeltaSeconds);

		VelocityLocomotionAngleWithOffset = FMath::UnwindDegrees(VelocityLocomotionAngle - RootYawOffset);

		bShouldTurnLeft = RootYawOffset > 0.f;

		/*UE_LOG(LogTemp, Warning, TEXT("Init class: %s"), *GetClass()->GetName());
		UE_LOG(LogTemp, Log, TEXT("%f"), RootYawOffset);*/
	}
}

void ULyraAnimInstance::UpdateCharacterGate()
{
	CharacterLastGate = CharacterCurrentGate;
	CharacterCurrentGate = ICharacterInterface::Execute_GetCharacterCurrentGate(PawnOwner);
	bIsCrouching = CharacterCurrentGate == ECharacterGate::ECG_Crouching;
	bLastFrameIsCrouching = CharacterLastGate == ECharacterGate::ECG_Crouching;
	bCrouchStateChanged = bIsCrouching != bLastFrameIsCrouching;
}

void ULyraAnimInstance::UpdateLocomotionDirection(const float Angle, ELocomotionDirection& Direction)
{
	switch (Direction)
	{
	case ELocomotionDirection::ELD_Forward:
		if(Angle>=ForwardMinBound-DeadZone && Angle<=ForwardMaxBound+DeadZone)return;
		break;
	case ELocomotionDirection::ELD_Backward:
		if(Angle<=BackwardMinBound+DeadZone || Angle>=BackwardMaxBound-DeadZone)return;
		break;
	case ELocomotionDirection::ELD_Right:
		if(Angle<=BackwardMaxBound+DeadZone && Angle>=ForwardMaxBound-DeadZone)return;
		break;
	case ELocomotionDirection::ELD_Left:
		if(Angle>=BackwardMinBound-DeadZone && Angle<=ForwardMinBound-DeadZone)return;
		break;
	default:
		break;	
	}
	if(Angle<=BackwardMinBound || Angle>=BackwardMaxBound)
	{
		Direction = ELocomotionDirection::ELD_Backward;
	}
	else if(Angle>=ForwardMinBound && Angle<=ForwardMaxBound)
	{
		Direction = ELocomotionDirection::ELD_Forward;
	}
	else if(Angle>0.f)
	{
		Direction = ELocomotionDirection::ELD_Right;
	}
	else
	{
		Direction = ELocomotionDirection::ELD_Left;
	}
}

void ULyraAnimInstance::CalculateLeanAngle(float DeltaSeconds)
{
	DeltaYaw = CurrentCharacterYaw - LastCharacterYaw;
	if(VelocityLocomotionDirection == ELocomotionDirection::ELD_Backward)
	{
		DeltaYaw *= -1;
	}
	LeanAngle = FMath::Clamp(DeltaYaw / DeltaSeconds / 5.f, -90.f, 90.f);
}

void ULyraAnimInstance::GetCharacterStopDistance()
{
	PawnOwner = PawnOwner == nullptr ? TryGetPawnOwner() : PawnOwner;
	if(PawnOwner && PawnOwner->Implements<UCharacterInterface>())
	{
		StopDistance = ICharacterInterface::Execute_PredictCharacterStopDistance(PawnOwner);
	}
}

void ULyraAnimInstance::GetCharacterMaxWalkSpeed()
{
	PawnOwner = PawnOwner == nullptr ? TryGetPawnOwner() : PawnOwner;
	if(PawnOwner && PawnOwner->Implements<UCharacterInterface>())
	{
		CharacterMaxWalkSpeed = ICharacterInterface::Execute_GetCharacterMaxWalkSpeed(PawnOwner);
	}
}

void ULyraAnimInstance::CalculateDeltaLocation()
{
	FVector DeltaLocation = CharacterCurrentLocation - CharacterLastLocation;
	DeltaLocation.Z = 0.f;
	CharacterDeltaLocation = DeltaLocation.Size();
}

void ULyraAnimInstance::GetCharacterPivotDistance()
{
	PawnOwner = PawnOwner == nullptr ? TryGetPawnOwner() : PawnOwner;
	if(PawnOwner && PawnOwner->Implements<UCharacterInterface>())
	{
		PivotDistance = ICharacterInterface::Execute_PredictCharacterPivotDistance(PawnOwner);
	}
}

void ULyraAnimInstance::UpdateRootYawOffset(float DeltaTime)
{
	if(RootYawOffsetMode == ERootYawOffsetMode::ERYOM_Accumulate)
	{
		RootYawOffset = FMath::UnwindDegrees(RootYawOffset - DeltaYaw);
	}
	else if(RootYawOffsetMode == ERootYawOffsetMode::ERYOM_BlendOut)
	{
		// 确保 SpringMass 不为零，避免除零错误
		float UndampedFrequency = 0.0f;
		if (SpringMass > KINDA_SMALL_NUMBER) 
		{
			UndampedFrequency = FMath::Sqrt(SpringStiffness / SpringMass);
		}
		FMath::SpringDamper(
			RootYawOffset,           // InOutValue - 会被修改
			RootYawOffsetVelocity,   // InOutValueRate - 会被修改，并保持状态
			TargetRootYawOffset,     // InTargetValue - 通常设为 0.0f 进行淡出
			0.f,  // InTargetValueRate - 目标速度，通常为 0.0f
			DeltaTime,               // InDeltaTime
			UndampedFrequency,       // InUndampedFrequency
			SpringDampingFactor      // InDampingRatio
		);
	}
}
