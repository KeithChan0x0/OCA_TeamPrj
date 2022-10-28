// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HorseAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class OCA_TEAMPRJ_API UHorseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UHorseAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly)
		float Speed = 0.0f;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly)
		float Direction = 0.0f;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly)
		bool IsInAir = false;
private:

	UPROPERTY(VisibleAnywhere, Transient)
	class APlayerCharacter* PlayerCharacter = nullptr;

	void OnUpdateIsInAir();
};
