// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/LyraCharacter.h"

#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "KismetAnimationLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AnimCharacterMovementLibrary.h"

ALyraCharacter::ALyraCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	JoggingGateSettings.MaxWalkSpeed = 800.f;
	JoggingGateSettings.MaxAcceleration = 800.f;
	JoggingGateSettings.BrakingDeceleration = 1200.f;
	JoggingGateSettings.BrakingFrictionFactor = 1.f;
	JoggingGateSettings.BrakingFriction = 0.f;
	JoggingGateSettings.UseSeparateBrakingFriction = true;

	WalkingGateSettings.MaxWalkSpeed = 250.f;
	WalkingGateSettings.MaxAcceleration = 250.f;
	WalkingGateSettings.BrakingDeceleration = 250.f;
	WalkingGateSettings.BrakingFrictionFactor = 1.f;
	WalkingGateSettings.BrakingFriction = 0.f;
	WalkingGateSettings.UseSeparateBrakingFriction = true;

	CrouchingGateSettings.MaxWalkSpeed = 250.f;
	CrouchingGateSettings.MaxAcceleration = 250.f;
	CrouchingGateSettings.BrakingDeceleration = 250.f;
	CrouchingGateSettings.BrakingFrictionFactor = 1.f;
	CrouchingGateSettings.BrakingFriction = 0.f;
	CrouchingGateSettings.UseSeparateBrakingFriction = true;
}

void ALyraCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(GetMesh() && AnimUnarmed)
	{
		GetMesh()->LinkAnimClassLayers(AnimUnarmed);
	}
	UpdateGate(ECharacterGate::ECG_Jogging);
	
}

void ALyraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}






/** 输入系统 **/

void ALyraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	LyraPlayerController = LyraPlayerController == nullptr ? Cast<APlayerController>(GetController()) : LyraPlayerController;

	if(LyraPlayerController)
	{
		if(ULocalPlayer* LocalPlayer = LyraPlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	if(UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(SwitchWeaponsAction)
		{
			EnhancedInput->BindAction(SwitchWeaponsAction, ETriggerEvent::Started, this, &ThisClass::OnAction_SwitchWeapons);
		}
		if(LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::OnAction_Look);
		}
		if(MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::OnAction_Move);
		}
		if(AimAction)
		{
			EnhancedInput->BindAction(AimAction, ETriggerEvent::Started, this, &ThisClass::OnAction_StartAim);
			EnhancedInput->BindAction(AimAction, ETriggerEvent::Completed, this, &ThisClass::OnAction_EndAim);
		}
		if(CrouchAction)
		{
			EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Started, this, &ThisClass::OnAction_Crouch);
		}
	}
}

void ALyraCharacter::OnAction_SwitchWeapons(const FInputActionValue& InputActionValue)
{
	switch(static_cast<int32>(InputActionValue.Get<float>()))
	{
	case 1:
		EquippedGunType = EGuns::EG_Rifle;
		if(GetMesh() && AnimRifle)
		{
			GetMesh()->LinkAnimClassLayers(AnimRifle);
		}
		break;
	case 2:
		EquippedGunType = EGuns::EG_Pistol;
		if(GetMesh() && AnimPistol)
		{
			GetMesh()->LinkAnimClassLayers(AnimPistol);
		}
		break;
	default:
		break;
	}
}

void ALyraCharacter::OnAction_Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookValue = InputActionValue.Get<FVector2D>();

	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(-LookValue.Y);
}

void ALyraCharacter::OnAction_Move(const FInputActionValue& InputActionValue)
{
	FVector2D MoveValue = InputActionValue.Get<FVector2D>();

	if(Controller && !MoveValue.IsZero())
	{
		const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
	
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
		AddMovementInput(ForwardDirection, MoveValue.Y);
		AddMovementInput(RightDirection, MoveValue.X);
	}
}

void ALyraCharacter::OnAction_StartAim(const FInputActionValue& InputActionValue)
{
	UpdateGate(ECharacterGate::ECG_Walking);
}

void ALyraCharacter::OnAction_EndAim(const FInputActionValue& InputActionValue)
{
	UpdateGate(ECharacterGate::ECG_Jogging);
}

void ALyraCharacter::OnAction_Crouch(const FInputActionValue& InputActionValue)
{
	if(CurrentGate == ECharacterGate::ECG_Crouching)
	{
		UnCrouch();
		UpdateGate(ECharacterGate::ECG_Jogging);
	}
	else
	{
		Crouch();
		UpdateGate(ECharacterGate::ECG_Crouching);
	}
}


/** 状态更新 **/
void ALyraCharacter::UpdateGate(ECharacterGate Gate)
{
	CurrentGate = Gate;
	switch (CurrentGate)
	{
	case ECharacterGate::ECG_Jogging:
		if(GetCharacterMovement())
		{
			GetCharacterMovement()->MaxWalkSpeed = JoggingGateSettings.MaxWalkSpeed;
			GetCharacterMovement()->MaxAcceleration = JoggingGateSettings.MaxAcceleration;
			GetCharacterMovement()->BrakingDecelerationWalking = JoggingGateSettings.BrakingDeceleration;
			GetCharacterMovement()->BrakingFriction = JoggingGateSettings.BrakingFriction;
			GetCharacterMovement()->bUseSeparateBrakingFriction = JoggingGateSettings.UseSeparateBrakingFriction;
		}
		break;
	case ECharacterGate::ECG_Walking:
		if(GetCharacterMovement())
		{
			GetCharacterMovement()->MaxWalkSpeed = WalkingGateSettings.MaxWalkSpeed;
			GetCharacterMovement()->MaxAcceleration = WalkingGateSettings.MaxAcceleration;
			GetCharacterMovement()->BrakingDecelerationWalking = WalkingGateSettings.BrakingDeceleration;
			GetCharacterMovement()->BrakingFriction = WalkingGateSettings.BrakingFriction;
			GetCharacterMovement()->bUseSeparateBrakingFriction = WalkingGateSettings.UseSeparateBrakingFriction;
		}
		break;
	case ECharacterGate::ECG_Crouching:
		if(GetCharacterMovement())
		{
			GetCharacterMovement()->MaxWalkSpeed = CrouchingGateSettings.MaxWalkSpeed;
			GetCharacterMovement()->MaxAcceleration = CrouchingGateSettings.MaxAcceleration;
			GetCharacterMovement()->BrakingDecelerationWalking = CrouchingGateSettings.BrakingDeceleration;
			GetCharacterMovement()->BrakingFriction = CrouchingGateSettings.BrakingFriction;
			GetCharacterMovement()->bUseSeparateBrakingFriction = CrouchingGateSettings.UseSeparateBrakingFriction;
		}
		break;
	default:
		break;	
	}
	
}


/** 接口实现 **/
EGuns ALyraCharacter::GetEquippedGunType_Implementation() const
{
	return EquippedGunType;
}

FVector2d ALyraCharacter::GetCharacterHorizontalVelocity_Implementation() const
{
	const FVector2d HorizontalVelocity = {GetVelocity().X, GetVelocity().Y};
	return HorizontalVelocity;
}

ECharacterGate ALyraCharacter::GetCharacterCurrentGate_Implementation() const
{
	return CurrentGate;
}

FRotator ALyraCharacter::GetCharacterRotation_Implementation() const
{
	return GetActorRotation();
}

float ALyraCharacter::GetCharacterOrientationData_Implementation() const
{
	return UKismetAnimationLibrary::CalculateDirection(GetVelocity(), GetActorRotation());
}

FVector2D ALyraCharacter::GetCharacterHorizontalAcceleration_Implementation() const
{
	FVector Acceleration = GetCharacterMovement()->GetCurrentAcceleration();
	return {Acceleration.X, Acceleration.Y};
}

bool ALyraCharacter::IsCharacterAccelerating_Implementation() const
{
	const FVector Acceleration = GetCharacterMovement()->GetCurrentAcceleration();
	const FVector2D HorizontalAcceleration = {Acceleration.X, Acceleration.Y};
	return !HorizontalAcceleration.IsNearlyZero();
}

float ALyraCharacter::PredictCharacterStopDistance_Implementation() const
{
	const FVector StopLocation = UAnimCharacterMovementLibrary::PredictGroundMovementStopLocation(
		{GetVelocity().X, GetVelocity().Y, 0.f},
		GetCharacterMovement()->bUseSeparateBrakingFriction,
		GetCharacterMovement()->BrakingFriction,
		GetCharacterMovement()->GroundFriction,
		GetCharacterMovement()->BrakingFrictionFactor,
		GetCharacterMovement()->BrakingDecelerationWalking
		);
	
	return StopLocation.Size();
}

float ALyraCharacter::GetCharacterMaxWalkSpeed_Implementation() const
{
	return GetCharacterMovement()->MaxWalkSpeed;
}

FVector ALyraCharacter::GetCharacterLocation_Implementation() const
{
	return GetActorLocation();
}

float ALyraCharacter::PredictCharacterPivotDistance_Implementation() const
{
	const FVector PivotLocation = UAnimCharacterMovementLibrary::PredictGroundMovementPivotLocation(
		GetCharacterMovement()->GetCurrentAcceleration(),
		{GetVelocity().X, GetVelocity().Y, 0.f},
		GetCharacterMovement()->GroundFriction
	);
	
	return PivotLocation.Size();
}




