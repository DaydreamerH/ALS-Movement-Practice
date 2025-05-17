
#pragma once

#include "CoreMinimal.h"
#include "CharacterInterfaces.h"
#include "InputActionValue.h"
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
	class UInputAction* SwitchWeaponsAction;
	UFUNCTION()
	void OnAction_SwitchWeapons(const FInputActionValue& InputActionValue);
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;
	UFUNCTION()
	void OnAction_Look(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	UFUNCTION()
	void OnAction_Move(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* AimAction;
	UFUNCTION()
	void OnAction_StartAim(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnAction_EndAim(const FInputActionValue& InputActionValue);


	
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
	
	ECharacterGate CurrentGate = ECharacterGate::ECG_Jogging;
	FGateSettings WalkingGateSettings;
	FGateSettings JoggingGateSettings;
	void UpdateGate(ECharacterGate Gate);
	

public:
	virtual EGuns GetEquippedGunType_Implementation() const override;
	virtual FVector2D GetCharacterHorizontalVelocity_Implementation() const override;
	virtual ECharacterGate GetCharacterCurrentGate_Implementation() const override;
	virtual FRotator GetCharacterRotation_Implementation() const override;
	virtual float GetCharacterOrientationData_Implementation() const override;
	virtual FVector2D GetCharacterHorizontalAcceleration_Implementation() const override;
	virtual bool IsCharacterAccelerating_Implementation() const override;
	virtual float PredictCharacterStopDistance_Implementation() const override;
	virtual float GetCharacterMaxWalkSpeed_Implementation() const override;
	virtual FVector GetCharacterLocation_Implementation() const override;
	virtual float PredictCharacterPivotDistance_Implementation() const override;
};
