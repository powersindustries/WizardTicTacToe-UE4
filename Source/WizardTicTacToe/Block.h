// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Block.generated.h"

UCLASS(minimalapi)
class ABlock : public AActor
{
	GENERATED_BODY()


public:
	ABlock();

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;
	UPROPERTY()
	class UMaterial* BaseMaterial;

	UPROPERTY()
	class UMaterialInstance* BlueMaterial;

	UPROPERTY()
	class UMaterialInstance* OrangeMaterial;

	UPROPERTY()
	class UMaterialInstance* GreenMaterial;

	UPROPERTY()
	class ABlockGrid* OwningGrid;

	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	FORCEINLINE class USceneComponent* GetRoot() const { return Root; }
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }


public:
	void HandleClicked();

	void SetBlockHighlighting(bool bOn);

	bool GetActiveState() { return IsActive; }
	void SetActiveState(bool state) { IsActive = state; }

	int GetBockIndex() { return BlockIndex; }
	void SetBlockIndex(int index) { BlockIndex = index; }


private:
	bool IsActive;

	int BlockIndex;

};



