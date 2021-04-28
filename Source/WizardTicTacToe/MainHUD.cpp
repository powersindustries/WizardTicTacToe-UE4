// FILL OUT YOUR COPYRIGHT NOTICE IN THE DESCRIPTION PAGE OF PROJECT SETTINGS.

#include "MainHUD.h"
#include "Blueprint/UserWidget.h"


AMainHUD::AMainHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> HUDObject(TEXT("/Game/UI/HUD"));
    HUDWidgetClass = HUDObject.Class;
}

void AMainHUD::BeginPlay()
{
    Super::BeginPlay();

    if (HUDWidgetClass != nullptr)
    {
        HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
        }
    }

}

void AMainHUD::DrawHUD()
{
    Super::DrawHUD();
}
