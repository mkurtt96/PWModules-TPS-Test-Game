// copyright mkurtt96


#include "ProjectWTPS/World/WorldDamageableActor.h"


AWorldDamageableActor::AWorldDamageableActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool AWorldDamageableActor::ApplyDamageFromParams_Implementation(USpellParams* Params)
{
	return true;
}

UObject* AWorldDamageableActor::GetEffectReceiver_Implementation()
{
	return IPWEffectReceiverInterface::GetEffectReceiver_Implementation();
}
