// copyright mkurtt96


#include "ProjectWTPS/UI/TPSHUD.h"

#include "Macros/LogMacros.h"
#include "ProjectWTPS/UI/TPSUserWidget.h"


void ATPSHUD::BeginPlay()
{
	Super::BeginPlay();

	InitializeHUD();
}

void ATPSHUD::InitializeHUD() const
{
	if (!OverlayWidgetClass)
	{
		logfuncmsgf("Overlay Widget Class is NULL!");
		return;
	}
	
	UUserWidget* Widget = CreateWidget(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
