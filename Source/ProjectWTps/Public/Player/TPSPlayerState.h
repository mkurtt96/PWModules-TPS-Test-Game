// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Ability/Damageable.h"
#include "Ability/Effectable.h"
#include "AttributeBases/PWAttributeSet_BasicAttribute.h"
#include "AttributeBases/PWAttributeSet_RegeneratingAttribute.h"
#include "GameFramework/PlayerState.h"
#include "TPSPlayerState.generated.h"

class UPWAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTWTPS_API ATPSPlayerState : public APlayerState, public IAbilitySystemInterface, public IDamageable, public IEffectable
{
	GENERATED_BODY()

public:
	ATPSPlayerState();

	RegeneratingAttribute(Health);
	RegeneratingAttribute(Mana);
	BasicAttribute(MovementSpeed);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPWAbilitySystemComponent> ASC;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UPWAbilitySystemComponent* GetASC();

	virtual bool ApplyDamage_Implementation(class USpellParams* Params) override;
	virtual bool ApplyEffects_Implementation(class USpellParams* Params) override;
};
