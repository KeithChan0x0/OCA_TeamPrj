// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SplinePath.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camrera"));
	CameraComp->SetupAttachment(SpringArmComp);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (FollowPathPtr) {
		FollowPath = FollowPathPtr.Get();
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FollowPath) {
		auto targetTransform = FollowPath->GetCurrentSplineWorldTransform();
		auto location = targetTransform.GetLocation();
		location.Z = GetTransform().GetLocation().Z;
		SetActorLocation(location);
		SetActorRotation(targetTransform.GetRotation());

		//SimpleMoveTo
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &APlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);

}

float APlayerCharacter::GetSpeed()
{
	return FollowPath ? FollowPath->GetSpeed() : 0.0f;
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void APlayerCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * InputRotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * InputRotationRate * GetWorld()->GetDeltaSeconds());
}

