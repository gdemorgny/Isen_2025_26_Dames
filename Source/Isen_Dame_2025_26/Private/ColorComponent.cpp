// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorComponent.h"

// Sets default values for this component's properties
UColorComponent::UColorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UColorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UColorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UColorComponent::ChangeMaterial(EColorType newType, UStaticMeshComponent* mesh) const
{
	switch (newType)
	{
	case EColorType::Empty:
		mesh->SetMaterial(0, BaseMaterial );
		break;
	case EColorType::White:
		mesh->SetMaterial(0, WhiteMaterial );
		break;
	case EColorType::Black:
		mesh->SetMaterial(0, BlackMaterial );

		break;
	case EColorType::Selected:
		mesh->SetMaterial(0, SelectedMaterial );

		break;
	case EColorType::Allowed:
		mesh->SetMaterial(0, AllowedMaterial );

		break;
		
	case EColorType::Wrong:
		mesh->SetMaterial(0, WrongMaterial );

		break;
	}
}
