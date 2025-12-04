// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSUserWidget.generated.h"

class UAttributeSet_Vitals;
class AProjectWTpsCharacter;
class ATPSPlayerController;
class ATPSPlayerState;
class UPWAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTWTPS_API UTPSUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	ATPSPlayerController* GetPC();
	UFUNCTION(BlueprintPure)
	ATPSPlayerState* GetPS();
	UFUNCTION(BlueprintPure)
	AProjectWTpsCharacter* GetCharacter();
	UFUNCTION(BlueprintPure)
	UPWAbilitySystemComponent* GetASC();
	
private:
	UPROPERTY()
	TWeakObjectPtr<ATPSPlayerController> CachedPC;
	UPROPERTY()
	TWeakObjectPtr<ATPSPlayerState> CachedPS;
	UPROPERTY()
	TWeakObjectPtr<AProjectWTpsCharacter> CachedCharacter;
	UPROPERTY()
	TWeakObjectPtr<UPWAbilitySystemComponent> CachedASC;

	
	
};
