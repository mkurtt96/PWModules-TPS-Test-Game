// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TPSHUD.generated.h"

class UTPSUserWidget;
/**
 * 
 */
UCLASS()
class PROJECTWTPS_API ATPSHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void InitializeHUD() const;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTPSUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UTPSUserWidget> OverlayWidget;
	
};
