// copyright mkurtt96


#include "Player/TPSPlayerState.h"

#include "GAS/ASC/PWAbilitySystemComponent.h"

ATPSPlayerState::ATPSPlayerState()
{
	ASC = CreateDefaultSubobject<UPWAbilitySystemComponent>("AbilitySystemComponent");
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void ATPSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	ASC->InitAbilityActorInfo(this, GetPawn());
}

UAbilitySystemComponent* ATPSPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

UPWAbilitySystemComponent* ATPSPlayerState::GetASC()
{
	return ASC;
}

bool ATPSPlayerState::ApplyDamage_Implementation(class USpellParams* Params)
{
	return IDamageable::ApplyDamage_Implementation(Params);
}

bool ATPSPlayerState::ApplyEffects_Implementation(class USpellParams* Params)
{
	return IEffectable::ApplyEffects_Implementation(Params);
}
