// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ColorComponent.generated.h"

UENUM(BlueprintType)
enum class EColorType : uint8
{
	Empty UMETA(DisplayName = "Empty"),
	White UMETA(DisplayName = "White"),
	Black UMETA(DisplayName = "Black"),
	Selected UMETA(DisplayName = "Selected"),
	Allowed UMETA(DisplayName = "Allowed"),
	Wrong UMETA(DisplayName = "Wrong"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ISEN_DAME_2025_26_API UColorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColorComponent();
	UPROPERTY(EditAnywhere)
	UMaterialInstance* WhiteMaterial;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* BlackMaterial;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* SelectedMaterial;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* AllowedMaterial;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* WrongMaterial;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* BaseMaterial;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void ChangeMaterial(EColorType newType, UStaticMeshComponent* mesh) const;
		
};
