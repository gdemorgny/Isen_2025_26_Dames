// Fill out your copyright notice in the Description page of Project Settings.


#include "DamePlayerController.h"

#include "Selectable.h"


void ADamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(GameplayMappingContext, 0);
	}
}

void ADamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent
		= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Select, ETriggerEvent::Started,
			this, &ADamePlayerController::TrySelect);
	}
}

void ADamePlayerController::TrySelect()
{
	//TODO : faire un raycast de la souris vers le monde
	// 1 récupèrer la position et forward de la souris directement en 3D
	FVector MousePos, MouseForward;
	DeprojectMousePositionToWorld(MousePos, MouseForward);
	// 2 parametres du raycast
	FHitResult HitResult;
	FVector EndPosition = MousePos + MouseForward * 1000.f;
	FCollisionQueryParams CollParams;
	CollParams.AddIgnoredActor(this->GetPawn());
	// 3 raycast d'après le forward
	if(GetWorld()->LineTraceSingleByChannel(HitResult,MousePos,EndPosition,
		ECC_Visibility,CollParams))
	{
		AActor* HitActor = HitResult.GetActor();
		if(HitActor->Implements<USelectable>() &&
			TScriptInterface<ISelectable>(HitActor)->IsAPawn())
		{
			if(SelectedPawn != nullptr && SelectedPawn != TScriptInterface<ISelectable>(HitActor))
			{
				SelectedPawn -> Unselect();
			} 
			SelectedPawn = TScriptInterface<ISelectable>(HitActor);
			SelectedPawn->Select();
			UE_LOG(LogTemp,Warning,TEXT("L'objet touché est %s"),*HitActor->GetName());
			
		} else if (SelectedPawn != nullptr)
		{
			SelectedPawn -> Unselect();
			SelectedPawn = nullptr;
		}
		
		
		//TODO : select un case seulement en seconde selection
	}
	
}
