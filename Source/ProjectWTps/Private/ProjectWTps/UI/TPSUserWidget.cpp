// copyright mkurtt96


#include "ProjectWTPS/UI/TPSUserWidget.h"

#include "ProjectWTPS/Character/ProjectWTpsCharacter.h"
#include "ProjectWTPS/Player/TPSPlayerController.h"
#include "ProjectWTPS/Player/TPSPlayerState.h"
#include "GAS/ASC/PWAbilitySystemComponent.h"

ATPSPlayerController* UTPSUserWidget::GetPC()
{
	if (!CachedPC.IsValid())
		CachedPC = GetOwningPlayer<ATPSPlayerController>();
	return CachedPC.Get();
}

ATPSPlayerState* UTPSUserWidget::GetPS()
{
	if (!CachedPS.IsValid())
		CachedPS = GetOwningPlayerState<ATPSPlayerState>();
	return CachedPS.Get();
}

AProjectWTpsCharacter* UTPSUserWidget::GetCharacter()
{
	if (!CachedCharacter.IsValid())
		CachedCharacter = Cast<AProjectWTpsCharacter>(GetOwningPlayerPawn());
	return CachedCharacter.Get();
}

UPWAbilitySystemComponent* UTPSUserWidget::GetASC()
{
	if (!CachedASC.IsValid())
		if (GetPS())
			CachedASC = GetPS()->GetASC();
	return CachedASC.Get();
}
