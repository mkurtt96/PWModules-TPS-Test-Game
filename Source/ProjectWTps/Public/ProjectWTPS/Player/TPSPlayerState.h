// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Ability/Damageable.h"
#include "Ability/Effectable.h"
#include "GameFramework/PlayerState.h"
#include "TPSPlayerState.generated.h"

class ATPSPlayerState;
struct FEffectProperties;
class UAttributeSet_Core;
class UPWAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS()
class PROJECTWTPS_API ATPSPlayerState : public APlayerState, public IAbilitySystemInterface, public IDamageable, public IEffectable
{
	GENERATED_BODY()

public:
	FOnDeathDelegate OnDeath;
	ATPSPlayerState();
	virtual bool ApplyDamage_Implementation(class USpellParams* Params) override;
	virtual bool ApplyEffects_Implementation(class USpellParams* Params) override;

	bool bIsAlive;
	void SetIsAlive(bool bAlive);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPWAbilitySystemComponent> ASC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAttributeSet_Core> AS;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UPWAbilitySystemComponent* GetASC() const;
	virtual UAttributeSet_Core* GetASCore() const;

	
};
