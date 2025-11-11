// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "FEffectProperties.h"
#include "Subsystems/WorldSubsystem.h"
#include "PWCombatEvents.generated.h"

#define GetCombatEvents() \
GetWorld()->GetSubsystem<UPWCombatEvents>() 

UCLASS()
class PROJECTWTPS_API UPWCombatEvents : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeath, const FEffectProperties&);
	FOnDeath OnDeath;
};
