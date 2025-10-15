// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorComponent.h"
#include "IColorControl.h"
#include "Selectable.h"
#include "GameFramework/Actor.h"
#include "DamePawn.generated.h"

UCLASS()
class ISEN_DAME_2025_26_API ADamePawn : public AActor, public IIColorControl, public ISelectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamePawn();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
	class ABoard* Board;
	// TODO : retrouver le nom de ce type de declaration
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void ChangeColor(EColorType NewColor) override;

	virtual void Select() override;
	virtual void Unselect() override;
	virtual bool IsAPawn() override;
};
