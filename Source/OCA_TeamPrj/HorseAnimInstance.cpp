// Fill out your copyright notice in the Description page of Project Settings.


#include "HorseAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UHorseAnimInstance::UHorseAnimInstance()
{
}

void UHorseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto* Mesh = GetSkelMeshComponent();
	if (!Mesh) return;

	PlayerCharacter = Cast<APlayerCharacter>(Mesh->GetOwner());
	if (!PlayerCharacter) return;

	OnUpdateIsInAir();

	//Speed = PlayerCharacterVel.Length();
	Speed = PlayerCharacter->GetSpeed();


	auto PlayerCharacterVel = PlayerCharacter->GetVelocity();
	auto rotationX = UKismetMathLibrary::MakeRotFromX(PlayerCharacterVel);
	auto rotatorDelta = UKismetMathLibrary::NormalizedDeltaRotator(PlayerCharacter->GetControlRotation(), rotationX);
	Direction = rotatorDelta.Yaw;
}

void UHorseAnimInstance::OnUpdateIsInAir()
{
	auto* charMove = PlayerCharacter->GetCharacterMovement();
	IsInAir = charMove && charMove->IsFalling();
}
