// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlockGrid.h"
#include "Block.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "CustomGameMode.h"


#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ABlockGrid::ABlockGrid()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root0"));
	RootComponent = Root;

	Size = 3;
	BlockSpacing = 300.f;
}

void ABlockGrid::BeginPlay()
{
	Super::BeginPlay();

	const int32 NumBlocks = Size * Size;

	for(int32 BlockIndex=0; BlockIndex < NumBlocks; ++BlockIndex)
	{
		float XOffset = (BlockIndex / Size) * BlockSpacing;
		float YOffset = (BlockIndex % Size) * BlockSpacing;

		FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();
		ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(BlockLocation, FRotator(0,0,0));

		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
			NewBlock->SetBlockIndex(BlockIndex);
		}

		BlockArray.Add(NewBlock);
	}
}

void ABlockGrid::DeactivateAllBlocks()
{
	int BlockArraySize = BlockArray.Num();
	for (int x=0; x < BlockArraySize; ++x)
	{
		BlockArray[x]->SetActiveState(true);
	}
}

void ABlockGrid::ResetGrid()
{
	int BlockArraySize = BlockArray.Num();
	for (int x=0; x < BlockArraySize; ++x)
	{
		ABlock* CurrentBlock = BlockArray[x];

		CurrentBlock->SetActiveState(false);

		CurrentBlock->GetBlockMesh()->SetMaterial(0, CurrentBlock->BlueMaterial);
	}
}

#undef LOCTEXT_NAMESPACE
