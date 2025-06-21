
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

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* CrouchAction;
	UFUNCTION()
	void OnAction_Crouch(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;
	UFUNCTION()
	void OnAction_Jump(const FInputActionValue& InputActionValue);
	
	
	/** Anim Layers **/
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> AnimLayers;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> AnimPistol;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> AnimRifle;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> AnimUnarmed;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> CurrentLinkedAnimLayer;
	
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
	FGateSettings CrouchingGateSettings;
	void UpdateGate(ECharacterGate Gate);
	
	float GroundDistance = 0.f;
	void UpdateGroundDistance();
	
public:
	virtual EGuns GetEquippedGunType_Implementation() const override;
	virtual FVector2d GetCharacterHorizontalVelocity_Implementation() const override;
	virtual ECharacterGate GetCharacterCurrentGate_Implementation() const override;
	virtual FRotator GetCharacterRotation_Implementation() const override;
	virtual float GetCharacterOrientationData_Implementation() const override;
	virtual FVector2D GetCharacterHorizontalAcceleration_Implementation() const override;
	virtual bool IsCharacterAccelerating_Implementation() const override;
	virtual float PredictCharacterStopDistance_Implementation() const override;
	virtual float GetCharacterMaxWalkSpeed_Implementation() const override;
	virtual FVector GetCharacterLocation_Implementation() const override;
	virtual float PredictCharacterPivotDistance_Implementation() const override;
	virtual USkeletalMeshComponent* GetMeshComponent_Implementation() const override;
	virtual ULayerAnimInstance* GetCurrentLinkedAnimInstance_Implementation() const override;
	virtual bool IsInAir_Implementation() const override;
	virtual float VerticalVelocity_Implementation() override;
	virtual float GetGravityZ_Implementation() const override;
	virtual float GetGroundDistance_Implementation() const override;
	virtual float GetAimRotationPitch_Implementation() const override;
};
