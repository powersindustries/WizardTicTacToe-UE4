// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomPlayerController.h"

ACustomPlayerController::ACustomPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
