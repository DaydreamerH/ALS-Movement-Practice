#include "AnimInstances/LayerAnimInstance.h"


void ULayerAnimInstance::SetDirection_Implementation(ELocomotionDirection Direction)
{
	VelocityLocomotionDirection = Direction;
}

void ULayerAnimInstance::SetCharacterCurrentGate_Implementation(ECharacterGate Gate)
{
	CharacterCurrentGate = Gate;
}

void ULayerAnimInstance::SetHorizontalAcceleration_Implementation(FVector2D Acceleration)
{
	HorizontalAcceleration = Acceleration;
}

void ULayerAnimInstance::SetHorizontalVelocity_Implementation(FVector2D Velocity)
{
	HorizontalVelocity = Velocity;
}

void ULayerAnimInstance::SetIsCrouching_Implementation(bool bCrouch)
{
	bIsCrouching = bCrouch;
}

void ULayerAnimInstance::SetPivotDistance_Implementation(float Distance)
{
	PivotDistance = Distance;
}

void ULayerAnimInstance::SetStopDistance_Implementation(float Distance)
{
	StopDistance = Distance;
}

void ULayerAnimInstance::SetCharacterDeltaLocation_Implementation(float Location)
{
	CharacterDeltaLocation = Location;
}

void ULayerAnimInstance::SetRootYawOffset_Implementation(float Offset)
{
	RootYawOffset = Offset;
}

void ULayerAnimInstance::SetShouldTurnLeft_Implementation(bool Left)
{
	bShouldTurnLeft = Left;
}

void ULayerAnimInstance::SetAccelerationLocomotionDirection_Implementation(ELocomotionDirection Direction)
{
	AccelerationLocomotionDirection = Direction;
}

void ULayerAnimInstance::SetCrouchStateChanged_Implementation(bool Change)
{
	bCrouchStateChanged = Change;
}

void ULayerAnimInstance::SetLeanAngle_Implementation(float Angle)
{
	LeanAngle = Angle;
}

void ULayerAnimInstance::SetAccelerationLocomotionAngle_Implementation(float Angle)
{
	AccelerationLocomotionAngle = Angle;
}

void ULayerAnimInstance::SetVelocityLocomotionAngle_Implementation(float Angle)
{
	VelocityLocomotionAngle = Angle;
}

void ULayerAnimInstance::SetVelocityLocomotionAngleWithOffset_Implementation(float Angle)
{
	VelocityLocomotionAngleWithOffset = Angle;
}

void ULayerAnimInstance::SetGroundDistance_Implementation(float GD)
{
	GroundDistance = GD;
}

void ULayerAnimInstance::SetIsInAir_Implementation(bool Air)
{
	bIsInAir = Air;
}

void ULayerAnimInstance::SetFallingTime_Implementation(float fallingTime)
{
	FallingTime = fallingTime;
}
