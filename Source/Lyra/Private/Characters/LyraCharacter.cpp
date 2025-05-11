// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/LyraCharacter.h"

#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ALyraCharacter::ALyraCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

void ALyraCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(GetMesh() && AnimLayers)
	{
		GetMesh()->LinkAnimClassLayers(AnimLayers);
	}
	
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
		const FVector RightDirection   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
		AddMovementInput(ForwardDirection, MoveValue.Y);
		AddMovementInput(RightDirection, MoveValue.X);
	}
}











/** 接口实现 **/
EGuns ALyraCharacter::GetEquippedGunType_Implementation() const
{
	return EquippedGunType;
}

FVector2D ALyraCharacter::GetCharacterHorizontalVelocity_Implementation() const
{
	const FVector2D HorizontalVelocity = {GetVelocity().X, GetVelocity().Y};
	return HorizontalVelocity;
}

