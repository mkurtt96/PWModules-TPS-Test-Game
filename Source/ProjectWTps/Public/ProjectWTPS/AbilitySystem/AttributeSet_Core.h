// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "PWAttributeSetBase.h"
#include "AttributeSet_Core.generated.h"


class ATPSPlayerState;

UCLASS()
class PROJECTWTPS_API UAttributeSet_Core : public UPWAttributeSetBase
{
	GENERATED_BODY()

public:
	UAttributeSet_Core();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

#pragma region Vital Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital") FGameplayAttributeData Health; UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, Health);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthMax, Category = "Vital") FGameplayAttributeData HealthMax; UFUNCTION() void OnRep_HealthMax(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, HealthMax, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, HealthMax);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegen, Category = "Vital") FGameplayAttributeData HealthRegen; UFUNCTION() void OnRep_HealthRegen(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, HealthRegen, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, HealthRegen);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Shield, Category = "Vital") FGameplayAttributeData Shield; UFUNCTION() void OnRep_Shield(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Shield, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, Shield);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ShieldMax, Category = "Vital") FGameplayAttributeData ShieldMax; UFUNCTION() void OnRep_ShieldMax(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ShieldMax, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, ShieldMax);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ShieldRegen, Category = "Vital") FGameplayAttributeData ShieldRegen; UFUNCTION() void OnRep_ShieldRegen(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ShieldRegen, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, ShieldRegen);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital") FGameplayAttributeData Mana; UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, Mana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaMax, Category = "Vital") FGameplayAttributeData ManaMax; UFUNCTION() void OnRep_ManaMax(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ManaMax, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, ManaMax);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegen, Category = "Vital") FGameplayAttributeData ManaRegen; UFUNCTION() void OnRep_ManaRegen(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ManaRegen, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, ManaRegen);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital") FGameplayAttributeData Stamina; UFUNCTION() void OnRep_Stamina(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Stamina, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, Stamina);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaMax, Category = "Vital") FGameplayAttributeData StaminaMax; UFUNCTION() void OnRep_StaminaMax(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, StaminaMax, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, StaminaMax);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegen, Category = "Vital") FGameplayAttributeData StaminaRegen; UFUNCTION() void OnRep_StaminaRegen(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, StaminaRegen, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, StaminaRegen);
#pragma endregion
#pragma region Offense Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackPower, Category = "Offense") FGameplayAttributeData AttackPower; UFUNCTION() void OnRep_AttackPower(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, AttackPower, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, AttackPower);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalChance, Category = "Offense") FGameplayAttributeData CriticalChance; UFUNCTION() void OnRep_CriticalChance(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CriticalChance, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, CriticalChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalPower, Category = "Offense") FGameplayAttributeData CriticalPower; UFUNCTION() void OnRep_CriticalPower(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CriticalPower, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, CriticalPower);
#pragma endregion
#pragma region Defense Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackResistance, Category = "Defense") FGameplayAttributeData AttackResistance; UFUNCTION() void OnRep_AttackResistance(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, AttackResistance, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, AttackResistance);
#pragma endregion
#pragma region Utility Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Utility") FGameplayAttributeData MovementSpeed; UFUNCTION() void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MovementSpeed, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, MovementSpeed);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Utility") FGameplayAttributeData AttackSpeed; UFUNCTION() void OnRep_AttackSpeed(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, AttackSpeed, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, AttackSpeed);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CooldownReduction, Category = "Utility") FGameplayAttributeData CooldownReduction; UFUNCTION() void OnRep_CooldownReduction(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CooldownReduction, OldValue); } ATTRIBUTE_ACCESSORS(ThisClass, CooldownReduction);
#pragma endregion
#pragma region Meta Attributes
	UPROPERTY(BlueprintReadOnly, Category = "Meta") FGameplayAttributeData IncomingDamage; ATTRIBUTE_ACCESSORS(ThisClass, IncomingDamage);
#pragma endregion

protected:
	void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const;
	void HandleIncomingDamage(const FEffectProperties& Props);
	void HandleDeath(const FEffectProperties& Props);

public:
	ATPSPlayerState* PlayerState;
	ATPSPlayerState* GetPS();

	
};
