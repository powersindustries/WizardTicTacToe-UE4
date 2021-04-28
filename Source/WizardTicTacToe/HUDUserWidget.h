// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUserWidget.generated.h"

UCLASS()
class WIZARDTICTACTOE_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:
    
    UPROPERTY(meta=(BindWidget))
    class UTextBlock* TitleText;

    UPROPERTY(meta=(BindWidget))
    class UTextBlock* PlayerTurnText;

    UPROPERTY(meta=(BindWidget))
    class UTextBlock* PlayerWonText;

    UPROPERTY(meta=(BindWidget))
    class UButton* ResetMatchButton;

    UPROPERTY(meta=(BindWidget))
    class UButton* Wizard1SpellButton;

    UPROPERTY(meta=(BindWidget))
    class UButton* Wizard2SpellButton;

    UFUNCTION()
    void OnResetMatchButton();

    UFUNCTION()
    void OnWizard1SpellButton();

    UFUNCTION()
    void OnWizard2SpellButton();


public:
    
    void NativeConstruct() override;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    void UpdateText();

};
