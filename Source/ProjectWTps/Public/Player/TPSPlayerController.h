// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSPlayerController.generated.h"

struct FGameplayTag;
class UPWInputRouter;
class UPWAbilitySystemComponent;
class UPWInputConfig;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PROJECTWTPS_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATPSPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UPWInputRouter> InputRouter;

	UFUNCTION()
	virtual void InputTagStarted(const FGameplayTag& InputTag);
	UFUNCTION()
	virtual void InputTagCompleted(const FGameplayTag& InputTag);


	UPROPERTY()
	TObjectPtr<UPWAbilitySystemComponent> ASC;
	UPWAbilitySystemComponent* GetASC();
};
