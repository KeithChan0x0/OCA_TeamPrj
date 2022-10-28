// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePath.h"
#include "Components/SplineComponent.h"
// Sets default values
ASplinePath::ASplinePath()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComp;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineComp->SetupAttachment(RootComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cube.Cube"), NULL, LOAD_None, NULL);
	MeshComp->SetStaticMesh(Mesh);
	MeshComp->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void ASplinePath::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASplinePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Distance += Speed * DeltaTime;
	auto transform = SplineComp->GetTransformAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Type::Local, false);

	MeshComp->SetRelativeLocation(transform.GetLocation());
	MeshComp->SetRelativeRotation(transform.GetRotation());

	if (IsLooping) {
		if (Distance > SplineComp->GetSplineLength()) {
			Distance = 0.0f;
		}
	}
}

USplineComponent* ASplinePath::GetSplineComp() const
{
	return SplineComp;
}

FTransform ASplinePath::GetCurrentSplineWorldTransform() const
{
	return SplineComp->GetTransformAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Type::World, false);
	//return MeshComp->GetRelativeTransform();
}

