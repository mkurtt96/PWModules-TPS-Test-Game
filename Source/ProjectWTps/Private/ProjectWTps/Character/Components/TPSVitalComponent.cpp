// copyright mkurtt96


#include "ProjectWTPS/Character/Components/TPSVitalComponent.h"

#include "AbilitySystemGlobals.h"
#include "GAS/ASC/PWAbilitySystemComponent.h"
#include "Macros/LogMacros.h"
#include "ProjectWTPS/AbilitySystem/AttributeSet_Vitals.h"


UTPSVitalComponent::UTPSVitalComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTPSVitalComponent::Initialize()
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (ASC)
	{
		warnfuncmsgf("is already initialized for character: %s.", *GetNameSafe(Owner));
		return;
	}
	
	ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);
	if (!ASC)
	{
		errorfuncmsgf("ASC is NULL for character: %s.", *GetNameSafe(Owner));
		return;
	}

	ASVitals = ASC->GetSet<UAttributeSet_Vitals>();
	if (!ASVitals)
	{
		errorfuncmsgf("UAttributeSet_Vitals is NULL for character: %s.", *GetNameSafe(Owner));
		return;
	}

	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetHealthAttribute()).AddUObject(this, &ThisClass::HandleHealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetHealthMaxAttribute()).AddUObject(this, &ThisClass::HandleHealthMaxChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetHealthRegenAttribute()).AddUObject(this, &ThisClass::HandleHealthRegenChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetShieldAttribute()).AddUObject(this, &ThisClass::HandleShieldChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetShieldMaxAttribute()).AddUObject(this, &ThisClass::HandleShieldMaxChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetShieldRegenAttribute()).AddUObject(this, &ThisClass::HandleShieldRegenChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetManaAttribute()).AddUObject(this, &ThisClass::HandleManaChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetManaMaxAttribute()).AddUObject(this, &ThisClass::HandleManaMaxChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetManaRegenAttribute()).AddUObject(this, &ThisClass::HandleManaRegenChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetStaminaAttribute()).AddUObject(this, &ThisClass::HandleStaminaChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetStaminaMaxAttribute()).AddUObject(this, &ThisClass::HandleStaminaMaxChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Vitals::GetStaminaRegenAttribute()).AddUObject(this, &ThisClass::HandleStaminaRegenChanged);

	
	HealthChanged.Broadcast(ASVitals->GetHealth(), ASVitals->GetHealthMax(), ASVitals->GetHealthRegen());
	ShieldChanged.Broadcast(ASVitals->GetShield(), ASVitals->GetShieldMax(), ASVitals->GetShieldRegen());
	ManaChanged.Broadcast(ASVitals->GetMana(), ASVitals->GetManaMax(), ASVitals->GetManaRegen());
	StaminaChanged.Broadcast(ASVitals->GetStamina(), ASVitals->GetStaminaMax(), ASVitals->GetStaminaRegen());
}

void UTPSVitalComponent::HandleHealthChanged(const FOnAttributeChangeData& Data) const
{
	HealthChanged.Broadcast(Data.NewValue, ASVitals->GetHealthMax(), ASVitals->GetHealthRegen());
}

void UTPSVitalComponent::HandleHealthMaxChanged(const FOnAttributeChangeData& Data) const
{
	HealthChanged.Broadcast(ASVitals->GetHealth(), Data.NewValue, ASVitals->GetHealthRegen());
}

void UTPSVitalComponent::HandleHealthRegenChanged(const FOnAttributeChangeData& Data) const
{
	HealthChanged.Broadcast(ASVitals->GetHealth(), ASVitals->GetHealthMax(), Data.NewValue);
}

void UTPSVitalComponent::HandleShieldChanged(const FOnAttributeChangeData& Data) const
{
	ShieldChanged.Broadcast(Data.NewValue, ASVitals->GetShieldMax(), ASVitals->GetShieldRegen());
}

void UTPSVitalComponent::HandleShieldMaxChanged(const FOnAttributeChangeData& Data) const
{
	ShieldChanged.Broadcast(ASVitals->GetShield(), Data.NewValue, ASVitals->GetShieldRegen());
}

void UTPSVitalComponent::HandleShieldRegenChanged(const FOnAttributeChangeData& Data) const
{
	ShieldChanged.Broadcast(ASVitals->GetShield(), ASVitals->GetShieldMax(), Data.NewValue);
}

void UTPSVitalComponent::HandleManaChanged(const FOnAttributeChangeData& Data) const
{
	ManaChanged.Broadcast(Data.NewValue, ASVitals->GetManaMax(), ASVitals->GetManaRegen());
}

void UTPSVitalComponent::HandleManaMaxChanged(const FOnAttributeChangeData& Data) const
{
	ManaChanged.Broadcast(ASVitals->GetMana(), Data.NewValue, ASVitals->GetManaRegen());
}

void UTPSVitalComponent::HandleManaRegenChanged(const FOnAttributeChangeData& Data) const
{
	ManaChanged.Broadcast(ASVitals->GetMana(), ASVitals->GetManaMax(), Data.NewValue);
}

void UTPSVitalComponent::HandleStaminaChanged(const FOnAttributeChangeData& Data) const
{
	StaminaChanged.Broadcast(Data.NewValue, ASVitals->GetStaminaMax(), ASVitals->GetStaminaRegen());
}

void UTPSVitalComponent::HandleStaminaMaxChanged(const FOnAttributeChangeData& Data) const
{
	StaminaChanged.Broadcast(ASVitals->GetStamina(), Data.NewValue, ASVitals->GetStaminaRegen());
}

void UTPSVitalComponent::HandleStaminaRegenChanged(const FOnAttributeChangeData& Data) const
{
	StaminaChanged.Broadcast(ASVitals->GetStamina(), ASVitals->GetStaminaMax(), Data.NewValue);
}
