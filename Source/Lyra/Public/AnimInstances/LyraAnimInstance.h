// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LyraAnimInstance.generated.h"

enum class EGuns : uint8;
class ALyraCharacter;
/**
 * 
 */
UCLASS()
class LYRA_API ULyraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	
};
