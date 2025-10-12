// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamePawn.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "Board.generated.h"

USTRUCT(BlueprintType)
struct FColumns
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATile*> Column;
};

USTRUCT(BlueprintType)
struct FPawnData 
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	uint8 XCoord;
	UPROPERTY(EditAnywhere)
	uint8 YCoord;
	UPROPERTY(EditAnywhere)
	ADamePawn* Pawn;
	UPROPERTY(EditAnywhere)
	int32 PlayerNumber;
};

UCLASS()
class ISEN_DAME_2025_26_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();
	//TODO : acces aux tiles
	UPROPERTY(editAnywhere)
	uint8 BoardSize = 10;
	UPROPERTY(editAnywhere)
	int32 TileSize = 256;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATile> BaseTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADamePawn> BaseDamePawn;
	UPROPERTY(EditAnywhere)
	TArray<FColumns> Rows;
	UPROPERTY(EditAnywhere)
	TArray<FPawnData> PawnDatas;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void InitializeBoard();
	
};
