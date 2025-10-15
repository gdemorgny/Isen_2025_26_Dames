// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "ColorComponent.h"





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
						newPawn->Board = this;
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

TArray<ATile*> ABoard::CheckMoves(uint8 Xpos, uint8 Ypos, int32 ActualPlayer)
{
	TArray<ATile*> TilesAllowed;	
	// TODO : tester d'abord le fait de manger avant le deplacement
	//Positions à tester
	TArray<int32> XPosToTests = {-1,1};
	TArray<int32> YPosToTests = {ActualPlayer,ActualPlayer};

	for(int i = 0; i < XPosToTests.Num(); i++)
	{
		if (IsTileInBoardLimit(Xpos+XPosToTests[i],Ypos+YPosToTests[i])
			&& IsTileInBoardLimit(Xpos+XPosToTests[i]*2,Ypos+YPosToTests[i]*2)) 
		{
			if(IsOtherPlayerOnTile(Xpos+XPosToTests[i],
				Ypos+YPosToTests[i],ActualPlayer)
				&& IsTileEmpty(Xpos+XPosToTests[i]*2,
				Ypos+YPosToTests[i]*2))
			{
				TilesAllowed.Add(Rows[Ypos+YPosToTests[i]*2].Column[Xpos+XPosToTests[i]*2]);
			}
		}
	}
	if(TilesAllowed.Num() == 0)
	{
		for(int i = 0; i < XPosToTests.Num(); i++)
		{
			if (IsTileInBoardLimit(Xpos+XPosToTests[i],Ypos+YPosToTests[i])) 
			{
				if(IsTileEmpty(Xpos+XPosToTests[i],
					Ypos+YPosToTests[i]))
				{
					TilesAllowed.Add(Rows[Ypos+YPosToTests[i]].Column[Xpos+XPosToTests[i]]);
				}
			}
		}
	}
	return TilesAllowed;
}

void ABoard::HighlightAllAllowedTiles(TArray<ATile*> Tiles)
{
	for(int i = 0; i < Tiles.Num(); i++)
	{
		TScriptInterface<ISelectable>(Tiles[i])->Select();
	}
}

void ABoard::ShowMoves(ADamePawn* Pawn)
{
	uint8 Xpos = GetPawnXposValue(Pawn);
	uint8 YPos = GetPawnYposValue(Pawn);
	int32 player = GetPlayerByPawn(Pawn);
	if(Xpos == -1 || YPos == -1 || player == 0)
	{
		UE_LOG(LogTemp,Error,TEXT("Pawn Not in PawnList ! (%d,%d,%d)"),Xpos,YPos,player);
		return;
	}
	MoveTiles =  CheckMoves(Xpos,YPos,player);
	if (MoveTiles.Num() > 0)
	{
		HighlightAllAllowedTiles(MoveTiles);
	}
}

bool ABoard::IsTileEmpty(uint8 Xpos, uint8 YPpos)
{
	bool bIsEmpty = true;
	for(int i = 0; i < PawnDatas.Num(); i++)
	{
		if(PawnDatas[i].XCoord == Xpos && PawnDatas[i].YCoord == YPpos)
		{
			bIsEmpty = false;
			break;
		}
	}
	return bIsEmpty;
}

bool ABoard::IsOtherPlayerOnTile(uint8 Xpos, uint8 Ypos, int32 Player)
{
	bool bIsOtherPlayerOnTile = false;
	for(int i = 0; i < PawnDatas.Num(); i++)
	{
		if(PawnDatas[i].XCoord == Xpos
			&& PawnDatas[i].YCoord == Ypos
			&& PawnDatas[i].PlayerNumber != Player)
		{
			bIsOtherPlayerOnTile = true;
			break;
		}
	}
	return bIsOtherPlayerOnTile;
	
}

bool ABoard::IsTileInBoardLimit(uint8 Xpos, uint8 Ypos)
{
	return Xpos > 0 && Xpos < BoardSize
		&& Ypos > 0 && Ypos < BoardSize;
}

uint8 ABoard::GetPawnXposValue(ADamePawn* Pawn)
{
	uint8 xpos = -1;
	for(int i = 0; i < PawnDatas.Num(); i++)
	{
		if(PawnDatas[i].Pawn == Pawn)
		{
			xpos = PawnDatas[i].XCoord;
			break;
		}
	}
	return xpos;
}

uint8 ABoard::GetPawnYposValue(ADamePawn* Pawn)
{
	uint8 ypos = -1;
	for(int i = 0; i < PawnDatas.Num(); i++)
	{
		if(PawnDatas[i].Pawn == Pawn)
		{
			ypos = PawnDatas[i].YCoord;
			break;
		}
	}
	return ypos;
}

int32 ABoard::GetPlayerByPawn(ADamePawn* Pawn)
{
	int32 player = 0;
	for(int i = 0; i < PawnDatas.Num(); i++)
	{
		if(PawnDatas[i].Pawn == Pawn)
		{
			player = PawnDatas[i].PlayerNumber;
			break;
		}
	}
	return player;
}

