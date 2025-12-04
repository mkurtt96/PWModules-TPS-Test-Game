// copyright mkurtt96


#include "ProjectWTPS/World/WorldDamageableActor.h"

#include "Libraries/GASCoreFunctions.h"
#include "ProjectWTPS/AbilitySystem/AttributeSet_Vitals.h"


AWorldDamageableActor::AWorldDamageableActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool AWorldDamageableActor::ApplyEffects_Implementation(class USpellParams* SpellParams)
{
	TArray<FEffectModifierValue> EffectModifierValues = UGASCoreFunctions::GetModifierValuesFromEffects(SpellParams, UAttributeSet_Vitals::GetIncomingDamageAttribute());
	for (FEffectModifierValue EMV : EffectModifierValues)
	{
		switch (EMV.DurationType)
		{
		case EGameplayEffectDurationType::Instant:
			DoDamage(EMV.Value);
			break;
		case EGameplayEffectDurationType::Infinite:
			GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, EMV]()
			{
				DoDamage(EMV.Value);
			}), EMV.Period, true);
			break;
		case EGameplayEffectDurationType::HasDuration:
			GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, EMV]()
			{
				DoDamage(EMV.Value);
			}), EMV.Period, true);
			GetWorldTimerManager().SetTimer(TimerHandle2, FTimerDelegate::CreateLambda([this]()
			{
				GetWorldTimerManager().ClearTimer(TimerHandle);
			}), EMV.Duration, false);
			break;
		}
	}
	
	return true;
}

UObject* AWorldDamageableActor::GetEffectReceiver_Implementation()
{
	return this;
}

void AWorldDamageableActor::DoDamage(float Value)
{
	Health -= Value;

	if (Health <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Destroy();
	}
}