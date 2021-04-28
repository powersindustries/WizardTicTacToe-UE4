// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.h"
#include "CustomGameMode.h"

#include "BlockGrid.generated.h"


UCLASS(minimalapi)
class ABlockGrid : public AActor
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;


public:
	ABlockGrid();

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;
	
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

	FORCEINLINE class USceneComponent* GetRoot() const { return Root; }
	
	void ResetGrid();

	void DeactivateAllBlocks();

	TArray<ABlock*> GetBlockArray() { return BlockArray; }


private:

	TArray<ABlock*> BlockArray;

};



