// Copyright Epic Games, Inc. All Rights Reserved.

#include "Block.h"
#include "BlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"


ABlock::ABlock()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GreenMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
			, GreenMaterial(TEXT("/Game/Puzzle/Meshes/GreenMaterial.GreenMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = Root;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(Root);
	BlockMesh->OnClicked.AddDynamic(this, &ABlock::BlockClicked);

	BaseMaterial   = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial   = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
	GreenMaterial  = ConstructorStatics.GreenMaterial.Get();
}

void ABlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void ABlock::HandleClicked()
{
	ACustomGameMode* const GameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	bool Player1Turn = GameMode->GetPlayer1Turn();
		
	if (GameMode->GetSpellSlotBeingUsed())
	{
		GameMode->ActivateSpellSlotDestruction(BlockIndex);

		GameMode->SetPlayer1Turn(!Player1Turn);
	}
	else if (!IsActive)
	{
		IsActive = true;

		GameMode->SetBlockState(BlockIndex);

		if (Player1Turn)
		{
			BlockMesh->SetMaterial(0, OrangeMaterial);
		}
		else
		{
			BlockMesh->SetMaterial(0, GreenMaterial);
		}

		bool PlayerWon = GameMode->CheckWinCondition();
		if (PlayerWon)
		{
			OwningGrid->DeactivateAllBlocks();

			GameMode->SetWinCondition(true);
		}
		else
		{
			GameMode->SetPlayer1Turn(!Player1Turn);
		}

	}
}

void ABlock::SetBlockHighlighting(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (IsActive)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
}
