// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePath.generated.h"

UCLASS()
class OCA_TEAMPRJ_API ASplinePath : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASplinePath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class USplineComponent* GetSplineComp() const;

	FTransform  GetCurrentSplineWorldTransform() const;

	float GetSpeed() const { return Speed; }
private:
	UPROPERTY(EditAnywhere, Category = "Spline")
		class USplineComponent* SplineComp;

	UPROPERTY(EditAnywhere, Category = "Spline")
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Spline")
		float Speed = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Spline")
		float Distance = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Spline")
		bool IsLooping = false;
};
