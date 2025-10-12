// Fill out your copyright notice in the Description page of Project Settings.


#include "DamePawn.h"

// Sets default values
ADamePawn::ADamePawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
}

// Called when the game starts or when spawned
void ADamePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamePawn::ChangeColor(EColorType NewColor)
{
	FindComponentByClass<UColorComponent>()->ChangeMaterial(NewColor,StaticMesh);
}

void ADamePawn::Select()
{
	
	FindComponentByClass<UColorComponent>()->BaseMaterial = Cast<UMaterialInstance>(StaticMesh->GetMaterial(0));
	ChangeColor(EColorType::Selected);
}

void ADamePawn::Unselect()
{
	ChangeColor(EColorType::Empty);
}

bool ADamePawn::IsAPawn()
{
	return true;
}

//void ADamePawn::ChangeColor(EColorType NewColor)
//{
//	FindComponentByClass<UColorComponent>()->ChangeMaterial(NewColor,StaticMesh);
//}

