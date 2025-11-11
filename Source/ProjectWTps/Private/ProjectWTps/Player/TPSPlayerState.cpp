// copyright mkurtt96


#include "ProjectWTPS/Player/TPSPlayerState.h"

#include "ProjectWTPS/AbilitySystem/AttributeSet_Core.h"
#include "GAS/ASC/PWAbilitySystemComponent.h"

ATPSPlayerState::ATPSPlayerState()
{
	ASC = CreateDefaultSubobject<UPWAbilitySystemComponent>("AbilitySystemComponent");
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AS = CreateDefaultSubobject<UAttributeSet_Core>("AttributeSet Core");

	SetNetUpdateFrequency(60);
}

bool ATPSPlayerState::ApplyDamage_Implementation(class USpellParams* Params)
{
	return IDamageable::ApplyDamage_Implementation(Params);
}

bool ATPSPlayerState::ApplyEffects_Implementation(class USpellParams* Params)
{
	return IEffectable::ApplyEffects_Implementation(Params);
}

void ATPSPlayerState::SetIsAlive(bool bAlive)
{
	bIsAlive = bAlive;
	if (!bIsAlive) OnDeath.Broadcast();
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

UPWAbilitySystemComponent* ATPSPlayerState::GetASC() const
{
	return ASC;
}

UAttributeSet_Core* ATPSPlayerState::GetASCore() const
{
	return AS;
}
