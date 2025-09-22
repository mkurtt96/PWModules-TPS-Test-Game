// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "Ability/Damageable.h"
#include "Ability/PWEffectReceiverInterface.h"
#include "GameFramework/Actor.h"
#include "WorldDamageableActor.generated.h"

UCLASS()
class PROJECTWTPS_API AWorldDamageableActor : public AActor, public IPWEffectReceiverInterface, public IDamageable
{
	GENERATED_BODY()

public:
	AWorldDamageableActor();
	
	// IDamageable
	virtual bool ApplyDamageFromParams_Implementation(USpellParamsBase* Params);
	
	// IPWEffectReceiverInterface
	virtual UObject* GetEffectReceiver_Implementation() override;
};
