// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AttributeLibrary.generated.h"

struct FGameplayTag;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTWTPS_API UAttributeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintPure, Category="AttributeLibrary|SpellFunctions")
	static AActor* GetAvatarActor(const UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintPure, Category="AttributeLibrary|AttributeFunctions")
	static FGameplayAttribute GetAttribute(const UAbilitySystemComponent* ASC, const FGameplayTag& AttributeTag);

	UFUNCTION(BlueprintPure, Category="AttributeLibrary|AttributeFunctions")
	static float GetAttributeValue(const UAbilitySystemComponent* ASC, const FGameplayTag& AttributeTag);
	
	UFUNCTION(BlueprintCallable, Category="AttributeLibrary|AttributeFunctions")
	static float SetAttributeValue(const UAbilitySystemComponent* ASC, const FGameplayTag& AttributeTag, float NewValue);
};
