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
};