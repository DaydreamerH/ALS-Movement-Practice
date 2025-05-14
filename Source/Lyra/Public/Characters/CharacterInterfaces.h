#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterInterfaces.generated.h"

UENUM(BlueprintType)
enum class EGuns : uint8
{
	EG_Unarmed UMETA(DisplayName="Unarmed"),
	EG_Rifle UMETA(DisplayName="Rifle"),
	EG_Pistol UMETA(DisplayName="Pistol"),

	EG_MAX UMETA(DisplayName="DefaultMax")
};

UENUM(BlueprintType)
enum class ECharacterGate : uint8
{
	ECG_Walking UMETA(DisplayName="Walking"),
	ECG_Jogging UMETA(DisplayName="Jogging"),

	ECG_MAX UMETA(DisplayName="DefaultMax")
};

USTRUCT(BlueprintType)
struct FGateSettings
{
	GENERATED_BODY()

	float MaxWalkSpeed;
	float MaxAcceleration;
	float BrakingDeceleration;
	float BrakingFrictionFactor;
	float BrakingFriction;
	bool UseSeparateBrakingFriction;
};

UENUM(BlueprintType)
enum class ELocomotionDirection : uint8
{
	ELD_Forward UMETA(DisplayName="Forward"),
	ELD_Backward UMETA(DisplayName="Backward"),
	ELD_Left UMETA(DisplayName="Left"),
	ELD_Right UMETA(DisplayName="Right")
};



UINTERFACE(Blueprintable)
class LYRA_API UCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class LYRA_API ICharacterInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	EGuns GetEquippedGunType() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	FVector2D GetCharacterHorizontalVelocity() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	ECharacterGate GetCharacterCurrentGate() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	FRotator GetCharacterRotation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	float GetCharacterOrientationData() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	FVector GetCharacterHorizontalAcceleration() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	bool IsCharacterAccelerating() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	float PredictCharacterStopDistance() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	float GetCharacterMaxWalkSpeed() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	FVector GetCharacterLocation() const;
};