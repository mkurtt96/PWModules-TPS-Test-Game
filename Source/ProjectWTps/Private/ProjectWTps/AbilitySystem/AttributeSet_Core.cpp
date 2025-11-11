// copyright mkurtt96


#include "ProjectWTPS/AbilitySystem/AttributeSet_Core.h"

#include "FEffectProperties.h"
#include "GameplayEffectExtension.h"
#include "ProjectWTPS/Tags/ProjectWTpsTags.h"
#include "Net/UnrealNetwork.h"
#include "ProjectWTPS/Player/TPSPlayerState.h"
#include "ProjectWTPS/Subsystems/PWCombatEvents.h"

UAttributeSet_Core::UAttributeSet_Core()
{
	TagsToAttributes.Add(PWTags::Attribute::Vital::Health, GetHealthAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::HealthMax, GetHealthMaxAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::HealthRegen, GetHealthRegenAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::Shield, GetShieldAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::ShieldMax, GetShieldMaxAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::ShieldRegen, GetShieldRegenAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::Mana, GetManaAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::ManaMax, GetManaMaxAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::ManaRegen, GetManaRegenAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::Stamina, GetStaminaAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::StaminaMax, GetStaminaMaxAttribute());
	TagsToAttributes.Add(PWTags::Attribute::Vital::StaminaRegen, GetStaminaRegenAttribute());

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

	// Vitals
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, HealthMax, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ShieldMax, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ShieldRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ManaMax, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ManaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, StaminaMax, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, StaminaRegen, COND_None, REPNOTIFY_Always);
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

	ClampAttributes(Attribute, NewValue);
}

void UAttributeSet_Core::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	// todo: if dead return
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetHealthMax()));
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetManaMax()));
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
		HandleIncomingDamage(Props);
}

void UAttributeSet_Core::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UAttributeSet_Core::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0, GetHealthMax());
	if (Attribute == GetShieldAttribute())
		NewValue = FMath::Clamp(NewValue, 0, GetShieldMax());
	if (Attribute == GetManaAttribute())
		NewValue = FMath::Clamp(NewValue, 0, GetManaMax());
	if (Attribute == GetStaminaAttribute())
		NewValue = FMath::Clamp(NewValue, 0, GetStaminaMax());
}

void UAttributeSet_Core::HandleIncomingDamage(const FEffectProperties& Props)
{
	float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0);
	if (LocalIncomingDamage <= 0) return;


	
	if (GetHealth() < LocalIncomingDamage)
	LocalIncomingDamage = GetHealth() + .1; // Error margin
	
	const float NewHealth = GetHealth() - LocalIncomingDamage;
	SetHealth(FMath::Clamp(NewHealth, 0.0f, GetHealthMax()));

	const bool bFatal = NewHealth <= 0;
	if (bFatal)
	{
		HandleDeath(Props);
	}
}

void UAttributeSet_Core::HandleDeath(const FEffectProperties& Props)
{
	GetPS()->bIsAlive = false;
	GetCombatEvents()->OnDeath.Broadcast(Props);
}

ATPSPlayerState* UAttributeSet_Core::GetPS()
{
	if (!PlayerState)
		PlayerState = Cast<ATPSPlayerState>(GetOwningActor());
	return PlayerState;
}
