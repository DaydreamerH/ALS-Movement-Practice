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
		CharacterLastGate = CharacterCurrentGate;
		CharacterCurrentGate = ICharacterInterface::Execute_GetCharacterCurrentGate(PawnOwner);
		
		
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
	}
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
	float DeltaYaw = CurrentCharacterYaw - LastCharacterYaw;
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
