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
		if(SwitchWeaponsActions)
		{
			EnhancedInput->BindAction(SwitchWeaponsActions, ETriggerEvent::Started, this, &ThisClass::OnAction_SwitchWeapons);
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

EGuns ALyraCharacter::GetEquippedGunType_Implementation() const
{
	return EquippedGunType;
}

