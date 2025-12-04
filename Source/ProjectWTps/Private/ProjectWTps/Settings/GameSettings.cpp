// copyright mkurtt96


#include "ProjectWTPS/Settings/GameSettings.h"

FName UGameSettings::GetCategoryName() const
{
	return TEXT("Game"); 
}

TArray<TSubclassOf<UGameplayEffect>> UGameSettings::GetDefaultEffects() const
{
	TArray<TSubclassOf<UGameplayEffect>> Result;
	Result.Reserve(DefaultEffects.Num());

	for (const TSoftClassPtr<UGameplayEffect>& SoftEffect : DefaultEffects)
	{
		if (UClass* EffectClass = SoftEffect.LoadSynchronous())
		{
			Result.Add(EffectClass); // class type for MakeOutgoingSpec, etc.
		}
	}
	return Result;
}

TArray<FInputToAbility> UGameSettings::GetDefaultInputToAbilities() const
{
	return DefaultInputToAbilities;
}

FGameplayTagContainer UGameSettings::GetDefaultAbilities() const
{
	return DefaultAbilities;
}

UPWInputConfig* UGameSettings::GetInputConfig() const
{
	return InputConfig.LoadSynchronous();
}
