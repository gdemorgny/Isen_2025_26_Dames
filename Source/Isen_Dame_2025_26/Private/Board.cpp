// Fill out your copyright notice in the Description page of Project Settings.

#include "ColorComponent.h"
#include "Board.h"




// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	InitializeBoard();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard::InitializeBoard()
{
	//Todo : Spawn 100 tiles en 10 x 10
	// Conseil : en faire apparaitre une puis plusieurs puis toutes bien rangées
	//Instiate<GameObject>(prefab,position,rotation)
	
	
	if(BaseTile != nullptr)
	{
		FVector NewPos(0,0,0);
		FRotator NewRot(0,0,0);
		FRotator PawnRot(0,90.0f,0);
		FActorSpawnParameters parameters;
		PawnDatas.SetNum((BoardSize/2-1)*BoardSize);
		uint8 pawnDatasIndex = 0;
		Rows.SetNum(BoardSize);
		for(int i = 0; i < BoardSize; i++)
		{
			Rows[i].Column.SetNum(BoardSize);
			
			for(int j = 0; j < BoardSize; j++)
			{
				NewPos.X  = TileSize*i;
				NewPos.Y  = TileSize*j;
				Rows[i].Column[j] = GetWorld()->SpawnActor<ATile>(BaseTile,NewPos,NewRot,parameters);
				if((i+j)%2 == 0)
				{
					if(Rows[i].Column[j]->Implements<UIColorControl>())
					{
						TScriptInterface<IIColorControl>(Rows[i].Column[j])->ChangeColor(EColorType::White);
					}
				} else
				{
					if(Rows[i].Column[j]->Implements<UIColorControl>())
					{
						TScriptInterface<IIColorControl>(Rows[i].Column[j])->ChangeColor(EColorType::Black);
					}
					if(i < 4 || i > 5)
					{
						ADamePawn* newPawn = GetWorld()->SpawnActor<ADamePawn>(BaseDamePawn,NewPos + FVector::UpVector*140.0f,PawnRot,parameters);
						
						PawnDatas[pawnDatasIndex].XCoord = j;
						PawnDatas[pawnDatasIndex].YCoord = i;
						PawnDatas[pawnDatasIndex].Pawn = newPawn;
						if(i < 4 )
						{
							if(newPawn->Implements<UIColorControl>())
							{
								//newPawn->ChangeColor(EColorType::White);
								TScriptInterface<IIColorControl>(newPawn)->ChangeColor(EColorType::White);
								PawnDatas[pawnDatasIndex].PlayerNumber = 1;
							}
						} else {
							if(newPawn->Implements<UIColorControl>())
							{
								//newPawn->ChangeColor(EColorType::Black);
								TScriptInterface<IIColorControl>(newPawn)->ChangeColor(EColorType::Black);
								PawnDatas[pawnDatasIndex].PlayerNumber = -1;
							}
							
							
						}
						pawnDatasIndex ++;
					}
				}
				
			}
		}
			
		
		UE_LOG(LogTemp,Warning,TEXT("Tile spawn !"))
	}
	
}

