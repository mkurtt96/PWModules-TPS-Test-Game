// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/ActorComponent.h"
#include "TPSVitalComponent.generated.h"

class UAttributeSet_Vitals;
class UPWAbilitySystemComponent;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FVitalAttributeChanged, float, Value, float, ValueMax, float, ValueRegen);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTWTPS_API UTPSVitalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTPSVitalComponent();
	
	UFUNCTION(BlueprintPure, Category = "Health")
	static UTPSVitalComponent* FindVitalComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UTPSVitalComponent>() : nullptr); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Initialize();
	
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;
	UPROPERTY()
	TObjectPtr<const UAttributeSet_Vitals> ASVitals;

	UPROPERTY(BlueprintAssignable)
	FVitalAttributeChanged HealthChanged;
	UPROPERTY(BlueprintAssignable)
	FVitalAttributeChanged ShieldChanged;
	UPROPERTY(BlueprintAssignable)
	FVitalAttributeChanged ManaChanged;
	UPROPERTY(BlueprintAssignable)
	FVitalAttributeChanged StaminaChanged;
	
	void HandleHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleHealthMaxChanged(const FOnAttributeChangeData& Data) const;
	void HandleHealthRegenChanged(const FOnAttributeChangeData& Data) const;
	void HandleShieldChanged(const FOnAttributeChangeData& Data) const;
	void HandleShieldMaxChanged(const FOnAttributeChangeData& Data) const;
	void HandleShieldRegenChanged(const FOnAttributeChangeData& Data) const;
	void HandleManaChanged(const FOnAttributeChangeData& Data) const;
	void HandleManaMaxChanged(const FOnAttributeChangeData& Data) const;
	void HandleManaRegenChanged(const FOnAttributeChangeData& Data) const;
	void HandleStaminaChanged(const FOnAttributeChangeData& Data) const;
	void HandleStaminaMaxChanged(const FOnAttributeChangeData& Data) const;
	void HandleStaminaRegenChanged(const FOnAttributeChangeData& Data) const;

public:
};
