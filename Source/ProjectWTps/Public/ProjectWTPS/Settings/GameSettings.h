// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "PWInputConfig.h"
#include "Engine/DeveloperSettings.h"
#include "GameSettings.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FInputToAbility
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="GAS", meta=(Categories="Input"))
	FGameplayTag InputTag;
	UPROPERTY(EditAnywhere, Category="GAS", meta=(Categories="Ability.Skill"))
	FGameplayTag AbilityTag;
};

UCLASS(config=Game, defaultconfig)
class PROJECTWTPS_API UGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	static const UGameSettings* Get(){ return GetDefault<UGameSettings>(); }
	virtual FName GetCategoryName() const override;

	TArray<TSubclassOf<UGameplayEffect>> GetDefaultEffects() const;
	TArray<FInputToAbility> GetDefaultInputToAbilities() const;
	FGameplayTagContainer GetDefaultAbilities() const;
	UPWInputConfig* GetInputConfig() const;

protected:
	UPROPERTY(EditDefaultsOnly, config, Category="GAS", meta=(AllowedClasses="GameplayEffect"))
	TArray<TSoftClassPtr<UGameplayEffect>> DefaultEffects;
	UPROPERTY(EditDefaultsOnly, config, BlueprintReadOnly, Category="GAS")
	TArray<FInputToAbility> DefaultInputToAbilities;
	UPROPERTY(EditDefaultsOnly, config, BlueprintReadOnly, Category="GAS", meta=(GameplayTagFilter = "Ability.Skill"))
	FGameplayTagContainer DefaultAbilities;
	UPROPERTY(EditDefaultsOnly, config, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UPWInputConfig> InputConfig;
};
