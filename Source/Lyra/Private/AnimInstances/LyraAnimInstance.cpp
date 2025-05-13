// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/LyraAnimInstance.h"

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
		HorizontalVelocity = ICharacterInterface::Execute_GetCharacterHorizontalVelocity(PawnOwner);
		CharacterCurrentGate = ICharacterInterface::Execute_GetCharacterCurrentGate(PawnOwner);
		VelocityLocomotionAngle = ICharacterInterface::Execute_GetCharacterOrientationData(PawnOwner);
		UpdateVelocityLocomotionDirection();
		
	}
}



void ULyraAnimInstance::UpdateVelocityLocomotionDirection()
{
	switch (VelocityLocomotionDirection)
	{
	case ELocomotionDirection::ELD_Forward:
		if(VelocityLocomotionAngle>=ForwardMinBound-DeadZone && VelocityLocomotionAngle<=ForwardMaxBound+DeadZone)return;
		break;
	case ELocomotionDirection::ELD_Backward:
		if(VelocityLocomotionAngle<=BackwardMinBound+DeadZone || VelocityLocomotionAngle>=BackwardMaxBound-DeadZone)return;
		break;
	case ELocomotionDirection::ELD_Right:
		if(VelocityLocomotionAngle<=BackwardMaxBound+DeadZone && VelocityLocomotionAngle>=ForwardMaxBound-DeadZone)return;
		break;
	case ELocomotionDirection::ELD_Left:
		if(VelocityLocomotionAngle>=BackwardMinBound-DeadZone && VelocityLocomotionAngle<=ForwardMinBound-DeadZone)return;
		break;
	default:
		break;	
	}
	if(VelocityLocomotionAngle<=BackwardMinBound || VelocityLocomotionAngle>=BackwardMaxBound)
	{
		VelocityLocomotionDirection = ELocomotionDirection::ELD_Backward;
	}
	else if(VelocityLocomotionAngle>=ForwardMinBound && VelocityLocomotionAngle<=ForwardMaxBound)
	{
		VelocityLocomotionDirection = ELocomotionDirection::ELD_Forward;
	}
	else if(VelocityLocomotionAngle>0.f)
	{
		VelocityLocomotionDirection = ELocomotionDirection::ELD_Right;
	}
	else
	{
		VelocityLocomotionDirection = ELocomotionDirection::ELD_Left;
	}
}
