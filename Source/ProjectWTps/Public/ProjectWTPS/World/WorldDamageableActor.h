// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "Ability/Affectable.h"
#include "Ability/EffectReceiver.h"
#include "GameFramework/Actor.h"
#include "WorldDamageableActor.generated.h"

UCLASS()
class PROJECTWTPS_API AWorldDamageableActor : public AActor, public IEffectReceiver, public IAffectable
{
	GENERATED_BODY()

public:
	AWorldDamageableActor();
	
protected:
	//~IAffectable
	virtual bool ApplyEffects_Implementation(class USpellParams* SpellParams) override;
	//~IPWEffectReceiverInterface
	virtual UObject* GetEffectReceiver_Implementation() override;
	
	float Health = 100;
	FTimerHandle TimerHandle;
	FTimerHandle TimerHandle2;
	
	void DoDamage(float Value);
	
};
