// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class WIZARDTICTACTOE_API AMainHUD : public AHUD
{
	GENERATED_BODY()


public:
	AMainHUD();

    virtual void BeginPlay() override;

    virtual void DrawHUD() override;


private:
    
    UPROPERTY(EditAnywhere, Category = "HUD")
    TSubclassOf<class UUserWidget> HUDWidgetClass;

    UPROPERTY(EditAnywhere, Category = "HUD")
    class UUserWidget* HUDWidget;

};
