
#pragma once

#include "CoreMinimal.h"
#include "CharacterInterfaces.h"
#include "GameFramework/Character.h"
#include "LyraCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class LYRA_API ALyraCharacter : public ACharacter, public ICharacterInterface
{
	GENERATED_BODY()

public:
	ALyraCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
	/** Inputs **/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	class UInputAction* SwitchWeaponsActions;
	UFUNCTION()
	void OnAction_SwitchWeapons(const FInputActionValue& InputActionValue);
	
	/** Anim Layers **/
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> AnimLayers;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> AnimPistol;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> AnimRifle;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> AnimUnarmed;
	
private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	
	UPROPERTY()
	APlayerController* LyraPlayerController;
	
	EGuns EquippedGunType = EGuns::EG_Unarmed;

public:
	virtual EGuns GetEquippedGunType_Implementation() const override;

	
};
