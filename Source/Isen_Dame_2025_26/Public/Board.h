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
	UPROPERTY(EditAnywhere)
	TArray<ATile*> MoveTiles;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void InitializeBoard();

	UFUNCTION()
	TArray<ATile*> CheckMoves(uint8 Xpos,uint8 YPpos, int32 ActualPlayer);

	UFUNCTION()
	void HighlightAllAllowedTiles(TArray<ATile*> Tiles);

	UFUNCTION()
	void ShowMoves(ADamePawn* Pawn);
	
private :
	bool IsTileEmpty(uint8 Xpos,uint8 Ypos);
	bool IsOtherPlayerOnTile(uint8 Xpos,uint8 Ypos, int32 Player);
	bool IsTileInBoardLimit(uint8 Xpos,uint8 Ypos);
	uint8 GetPawnXposValue(ADamePawn* Pawn);
	uint8 GetPawnYposValue(ADamePawn* Pawn);
	int32 GetPlayerByPawn(ADamePawn* Pawn);
};
