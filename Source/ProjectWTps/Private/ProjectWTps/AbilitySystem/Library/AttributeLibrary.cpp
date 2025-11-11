// copyright mkurtt96


#include "ProjectWTps/AbilitySystem/Library/AttributeLibrary.h"

#include "AbilitySystemComponent.h"
#include "ProjectWTPS/AbilitySystem/AttributeSet_Core.h"

AActor* UAttributeLibrary::GetAvatarActor(const UAbilitySystemComponent* ASC)
{
	if (!ASC)
	{
		UE_LOG(LogTemp, Log, TEXT("AbilitySystemComponent is null"));
		return nullptr;
	}

	AActor* AvatarActor = ASC->GetAvatarActor();
	if (!AvatarActor)
	{
		UE_LOG(LogTemp, Log, TEXT("AvatarActor is null"));
	}
	
	return AvatarActor;
}

FGameplayAttribute UAttributeLibrary::GetAttribute(const UAbilitySystemComponent* ASC, const FGameplayTag& AttributeTag)
{
	const UAttributeSet_Core* AS = Cast<const UAttributeSet_Core>(ASC->GetAttributeSet(UAttributeSet_Core::StaticClass()));
	if (!AS)
	{
		UE_LOG(LogTemp, Log, TEXT("AttributeSet is null"));
		return 0;
	}

	return AS->GetAttribute(AttributeTag);
}

float UAttributeLibrary::GetAttributeValue(const UAbilitySystemComponent* ASC, const FGameplayTag& AttributeTag)
{
	const UAttributeSet_Core* AS = Cast<const UAttributeSet_Core>(ASC->GetAttributeSet(UAttributeSet_Core::StaticClass()));
	if (!AS)
	{
		UE_LOG(LogTemp, Log, TEXT("AttributeSet is null"));
		return 0;
	}

	return AS->GetAttributeValue(AttributeTag);
}

float UAttributeLibrary::SetAttributeValue(const UAbilitySystemComponent* ASC, const FGameplayTag& AttributeTag, float NewValue)
{
	UAttributeSet_Core* AS = const_cast<UAttributeSet_Core*>(Cast<UAttributeSet_Core>(ASC->GetAttributeSet(UAttributeSet_Core::StaticClass())));
	if (!AS)
	{
		UE_LOG(LogTemp, Log, TEXT("AttributeSet is null"));
		return 0;
	}
	
	AS->SetAttributeValue(AttributeTag, NewValue);
	return NewValue;
}
