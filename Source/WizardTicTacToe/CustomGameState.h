// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameState.generated.h"


UENUM()
enum class BlockStates
{
	ENone,
	EPlayer1,
	EPlayer2
};


UCLASS()
class WIZARDTICTACTOE_API ACustomGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACustomGameState();
	~ACustomGameState();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Player1Turn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayerHasWon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Player1HasSpellslot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Player2HasSpellslot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SpellSlotBeingUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<BlockStates> BlockStateArray;


private:
	int BlockStateSize = 9;


};
