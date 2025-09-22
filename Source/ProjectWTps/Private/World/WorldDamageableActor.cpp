// copyright mkurtt96


#include "World/WorldDamageableActor.h"


AWorldDamageableActor::AWorldDamageableActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool AWorldDamageableActor::ApplyDamageFromParams_Implementation(USpellParamsBase* Params)
{
	return true;
}

UObject* AWorldDamageableActor::GetEffectReceiver_Implementation()
{
	return IPWEffectReceiverInterface::GetEffectReceiver_Implementation();
}
