// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"



UCLASS(minimalapi)
class ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACustomGameMode();
	~ACustomGameMode();

	
	UFUNCTION(BlueprintPure, Category="Player1Turn")
	virtual bool GetPlayer1Turn() const;

	UFUNCTION(BlueprintCallable, Category = "Player1Turn")
	virtual void SetPlayer1Turn(bool player1Turn);

	UFUNCTION(BlueprintCallable, Category = "BlockStateArray")
	virtual void SetBlockState(int index);

	UFUNCTION(BlueprintCallable, Category = "WinCondition")
	virtual bool GetWinCondition();

	UFUNCTION(BlueprintCallable, Category = "WinCondition")
	virtual void SetWinCondition(bool playerHasWon);

	UFUNCTION(BlueprintCallable, Category = "HasSpellSlot")
	virtual bool GetPlayer1HasSpellSlot();

	UFUNCTION(BlueprintCallable, Category = "HasSpellSlot")
	virtual void SetPlayer1HasSpellSlot(bool hasSpellSlot);

	UFUNCTION(BlueprintCallable, Category = "HasSpellSlot")
	virtual bool GetPlayer2HasSpellSlot();

	UFUNCTION(BlueprintCallable, Category = "HasSpellSlot")
	virtual void SetPlayer2HasSpellSlot(bool hasSpellSlot);

	UFUNCTION(BlueprintCallable, Category = "HasSpellSlot")
	virtual bool GetSpellSlotBeingUsed();

	UFUNCTION(BlueprintCallable, Category = "HasSpellSlot")
	virtual void SetSpellSlotBeingUsed(bool hasSpellSlot);

	UFUNCTION(BlueprintCallable, Category = "HasSpellSlot")
	virtual void ActivateSpellSlotDestruction(int index);


public:	
	virtual void StartPlay();

	bool CheckWinCondition();

	void ResetMatch();

};



