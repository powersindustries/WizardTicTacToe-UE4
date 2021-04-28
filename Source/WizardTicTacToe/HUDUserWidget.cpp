// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDUserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "Engine/World.h"
#include "CustomGameMode.h"


void UHUDUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ResetMatchButton->OnClicked.AddUniqueDynamic(this, &UHUDUserWidget::OnResetMatchButton);
    Wizard1SpellButton->OnClicked.AddUniqueDynamic(this, &UHUDUserWidget::OnWizard1SpellButton);
    Wizard2SpellButton->OnClicked.AddUniqueDynamic(this, &UHUDUserWidget::OnWizard2SpellButton);

}

void UHUDUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    UpdateText();
}

void UHUDUserWidget::UpdateText()
{
	ACustomGameMode* const GameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	bool Player1Turn = GameMode->GetPlayer1Turn();

    if (GameMode->GetWinCondition())
    {
        PlayerWonText->SetVisibility(ESlateVisibility::Visible);
        
        if (Player1Turn)
        {
            PlayerWonText->SetText(FText::FromString("Wizard 1 Wins!"));
        }
        else
        {
            PlayerWonText->SetText(FText::FromString("Wizard 2 Wins!"));
        }

        Wizard1SpellButton->SetIsEnabled(false);
        Wizard2SpellButton->SetIsEnabled(false);
    }
    else
    {
        PlayerWonText->SetVisibility(ESlateVisibility::Hidden);
    
        if (Player1Turn)
        {
            Wizard1SpellButton->SetIsEnabled(GameMode->GetPlayer1HasSpellSlot());
            Wizard2SpellButton->SetIsEnabled(false);
        }
        else
        {
            Wizard1SpellButton->SetIsEnabled(false);
            Wizard2SpellButton->SetIsEnabled(GameMode->GetPlayer2HasSpellSlot());
        }
    }

    if (Player1Turn)
    {
        PlayerTurnText->SetText(FText::FromString("Wizard 1's Turn."));
    }
    else
    {
        PlayerTurnText->SetText(FText::FromString("Wizard 2's Turn."));
    }

}

void UHUDUserWidget::OnResetMatchButton()
{
	ACustomGameMode* const GameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();
    GameMode->ResetMatch();
}

void UHUDUserWidget::OnWizard1SpellButton()
{
	ACustomGameMode* const GameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();

    if (GameMode->GetPlayer1HasSpellSlot())
    {
        GameMode->SetPlayer1HasSpellSlot(false);
    
        GameMode->SetSpellSlotBeingUsed(true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No spellslot available for Wizard 1"));
    }
}

void UHUDUserWidget::OnWizard2SpellButton()
{
	ACustomGameMode* const GameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();

    if (GameMode->GetPlayer2HasSpellSlot())
    {
        GameMode->SetPlayer2HasSpellSlot(false);
    
        GameMode->SetSpellSlotBeingUsed(true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No spellslot available for Wizard 2"));
    }
}
