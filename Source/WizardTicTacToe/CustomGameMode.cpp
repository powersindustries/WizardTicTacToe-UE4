// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomGameMode.h"
#include "CustomPlayerController.h"
#include "CustomPawn.h"
#include "CustomGameState.h"
#include "HUDUserWidget.h"
#include "MainHUD.h"
#include "BlockGrid.h"


ACustomGameMode::ACustomGameMode()
{
	GameStateClass = ACustomGameState::StaticClass();

	DefaultPawnClass = ACustomPawn::StaticClass();
	
	PlayerControllerClass = ACustomPlayerController::StaticClass();

	GameStateClass = ACustomGameState::StaticClass();

    HUDClass = AMainHUD::StaticClass();
}

ACustomGameMode::~ACustomGameMode()
{
}

void ACustomGameMode::StartPlay()
{
	Super::StartPlay();
}

bool ACustomGameMode::GetPlayer1Turn() const
{
	return GetGameState<ACustomGameState>()->Player1Turn;
}

void ACustomGameMode::SetPlayer1Turn(bool player1Turn)
{
	GetGameState<ACustomGameState>()->Player1Turn = player1Turn;
}

void ACustomGameMode::SetBlockState(int index)
{
	if (GetPlayer1Turn())
	{
		GetGameState<ACustomGameState>()->BlockStateArray[index] = BlockStates::EPlayer1;
	}
	else
	{
		GetGameState<ACustomGameState>()->BlockStateArray[index] = BlockStates::EPlayer2;
	}
}

bool ACustomGameMode::GetWinCondition()
{
	return GetGameState<ACustomGameState>()->PlayerHasWon;
}

void ACustomGameMode::SetWinCondition(bool playerHasWon)
{
    GetGameState<ACustomGameState>()->PlayerHasWon = playerHasWon;
}

bool ACustomGameMode::GetPlayer1HasSpellSlot()
{
    return GetGameState<ACustomGameState>()->Player1HasSpellslot;
}

void ACustomGameMode::SetPlayer1HasSpellSlot(bool hasSpellSlot)
{
    GetGameState<ACustomGameState>()->Player1HasSpellslot = hasSpellSlot;
}

bool ACustomGameMode::GetPlayer2HasSpellSlot()
{
    return GetGameState<ACustomGameState>()->Player2HasSpellslot;
}

void ACustomGameMode::SetPlayer2HasSpellSlot(bool hasSpellSlot)
{
    GetGameState<ACustomGameState>()->Player2HasSpellslot = hasSpellSlot;
}

bool ACustomGameMode::GetSpellSlotBeingUsed()
{
    return GetGameState<ACustomGameState>()->SpellSlotBeingUsed;
}

void ACustomGameMode::SetSpellSlotBeingUsed(bool hasSpellSlot)
{
    GetGameState<ACustomGameState>()->SpellSlotBeingUsed = hasSpellSlot;
}

void ACustomGameMode::ActivateSpellSlotDestruction(int index)
{
    int RandomSeed = FMath::RandRange(0,100);
    bool DestroysRows = RandomSeed > 50;

    int firstIndex = 0;
    int secondIndex = 0;
    int thirdIndex = 0;

    if (DestroysRows)
    {
        if (index == 0 || index == 1 || index == 2)
        {
            firstIndex  = 0;
            secondIndex = 1;
            thirdIndex  = 2;
        }
        else if (index == 3 || index == 4 || index == 5)
        {
            firstIndex  = 3;
            secondIndex = 4;
            thirdIndex  = 5;
        }
        else
        {
            firstIndex  = 6;
            secondIndex = 7;
            thirdIndex  = 8;
        }
    }
    else
    {
        if (index == 0 || index == 3 || index == 6)
        {
            firstIndex  = 0;
            secondIndex = 3;
            thirdIndex  = 6;
        }
        else if (index == 1 || index == 4 || index == 7)
        {
            firstIndex  = 1;
            secondIndex = 4;
            thirdIndex  = 7;
        }
        else
        {
            firstIndex  = 2;
            secondIndex = 5;
            thirdIndex  = 8;
        }
    }

    GetGameState<ACustomGameState>()->BlockStateArray[firstIndex]  = BlockStates::ENone;
    GetGameState<ACustomGameState>()->BlockStateArray[secondIndex] = BlockStates::ENone;
    GetGameState<ACustomGameState>()->BlockStateArray[thirdIndex]  = BlockStates::ENone;

    for (TObjectIterator<ABlockGrid> Itr; Itr; ++Itr)
    {
        if (Itr->IsA(ABlockGrid::StaticClass()))
        {
            if (Itr->GetBlockArray().Num() == 0)
            {
                continue;
            }

            TArray<ABlock*> Blocks = Itr->GetBlockArray();

            Blocks[firstIndex]->SetActiveState(false);
            Blocks[firstIndex]->GetBlockMesh()->SetMaterial(0, Blocks[firstIndex]->BlueMaterial);

            Blocks[secondIndex]->SetActiveState(false);
            Blocks[secondIndex]->GetBlockMesh()->SetMaterial(0, Blocks[secondIndex]->BlueMaterial);

            Blocks[thirdIndex]->SetActiveState(false);
            Blocks[thirdIndex]->GetBlockMesh()->SetMaterial(0, Blocks[thirdIndex]->BlueMaterial);

        }
    }

    SetSpellSlotBeingUsed(false);
}

bool ACustomGameMode::CheckWinCondition()
{
	ACustomGameState* CurrentGameState = GetGameState<ACustomGameState>();

	// First Row
	if (CurrentGameState->BlockStateArray[0] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[1] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[2] == BlockStates::EPlayer1
     || CurrentGameState->BlockStateArray[0] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[1] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[2] == BlockStates::EPlayer2)
	{
		return true;
	}

    // Second Row
    if (CurrentGameState->BlockStateArray[3] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[4] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[5] == BlockStates::EPlayer1
     || CurrentGameState->BlockStateArray[3] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[4] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[5] == BlockStates::EPlayer2)
    {
        return true;
    }

    // Third Row
    if (CurrentGameState->BlockStateArray[6] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[7] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[8] == BlockStates::EPlayer1
     || CurrentGameState->BlockStateArray[6] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[7] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[8] == BlockStates::EPlayer2)
    {
        return true;
    }

    // First Column
    if (CurrentGameState->BlockStateArray[0] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[3] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[6] == BlockStates::EPlayer1
     || CurrentGameState->BlockStateArray[0] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[3] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[6] == BlockStates::EPlayer2)
    {
        return true;
    }

    // Second Column
    if (CurrentGameState->BlockStateArray[1] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[4] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[7] == BlockStates::EPlayer1
     || CurrentGameState->BlockStateArray[1] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[4] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[7] == BlockStates::EPlayer2)
    {
        return true;
    }

    // Third Column
    if (CurrentGameState->BlockStateArray[2] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[5] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[8] == BlockStates::EPlayer1
     || CurrentGameState->BlockStateArray[2] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[5] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[8] == BlockStates::EPlayer2)
    {
        return true;
    }

    // Left Right Diagonal
    if (CurrentGameState->BlockStateArray[0] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[4] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[8] == BlockStates::EPlayer1
     || CurrentGameState->BlockStateArray[0] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[4] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[8] == BlockStates::EPlayer2)
    {
        return true;
    }

    // Right Left Diagonal
    if (CurrentGameState->BlockStateArray[2] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[4] == BlockStates::EPlayer1 && CurrentGameState->BlockStateArray[6] == BlockStates::EPlayer1
     || CurrentGameState->BlockStateArray[2] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[4] == BlockStates::EPlayer2 && CurrentGameState->BlockStateArray[6] == BlockStates::EPlayer2)
    {
        return true;
    }

	return false;
}

void ACustomGameMode::ResetMatch()
{
    SetWinCondition(false);

    SetPlayer1Turn(true);

    SetWinCondition(false);

    SetPlayer1HasSpellSlot(true);

    SetPlayer2HasSpellSlot(true);

    SetSpellSlotBeingUsed(false);

    int BlockStatesLength = GetGameState<ACustomGameState>()->BlockStateArray.Num();
    for (int x=0; x < BlockStatesLength; ++x)
    {
        GetGameState<ACustomGameState>()->BlockStateArray[x] = BlockStates::ENone;
    }

    for (TObjectIterator<ABlockGrid> Itr; Itr; ++Itr)
    {
        if (Itr->IsA(ABlockGrid::StaticClass()))
        {
            Itr->ResetGrid();
        }
    }
}
