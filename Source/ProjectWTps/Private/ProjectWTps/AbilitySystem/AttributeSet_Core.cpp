// copyright mkurtt96


#include "ProjectWTPS/AbilitySystem/AttributeSet_Core.h"

#include "GameplayEffectExtension.h"
#include "ProjectWTPS/Tags/ProjectWTpsTags.h"
#include "Net/UnrealNetwork.h"
#include "ProjectWTPS/Player/TPSPlayerState.h"

UAttributeSet_Core::UAttributeSet_Core()
{
	TagsToAttributes.Add(PWTags::Attribute::Offense::AttackPower, GetAttackPowerAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Offense::CriticalChance, GetCriticalChanceAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Offense::CriticalPower, GetCriticalPowerAttribute());

	TagsToAttributes.Add(PWTags::Attribute::Defense::AttackResistance, GetAttackResistanceAttribute());

	TagsToAttributes.Add(PWTags::Attribute::Utility::MovementSpeed, GetMovementSpeedAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Utility::AttackSpeed, GetAttackSpeedAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Utility::CooldownReduction, GetCooldownReductionAttribute());
}

void UAttributeSet_Core::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Offense
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CriticalPower, COND_None, REPNOTIFY_Always);
	// Defense
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, AttackResistance, COND_None, REPNOTIFY_Always);
	// Utility
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CooldownReduction, COND_None, REPNOTIFY_Always);
}

void UAttributeSet_Core::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UAttributeSet_Core::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UAttributeSet_Core::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

ATPSPlayerState* UAttributeSet_Core::GetPS()
{
	if (!PS)
		PS = Cast<ATPSPlayerState>(GetOwningActor());
	return PS;
}
