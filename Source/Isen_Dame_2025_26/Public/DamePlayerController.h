// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Selectable.h"
#include "GameFramework/PlayerController.h"
#include "DamePlayerController.generated.h"


UCLASS()
class ISEN_DAME_2025_26_API ADamePlayerController : public APlayerController
{
	GENERATED_BODY()
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* GameplayMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Select;

	UPROPERTY()
	TScriptInterface<ISelectable> SelectedPawn;
	
	UFUNCTION()
	void TrySelect();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
};
