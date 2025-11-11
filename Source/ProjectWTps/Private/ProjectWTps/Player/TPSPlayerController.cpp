// copyright mkurtt96


#include "ProjectWTPS/Player/TPSPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "PWInputRouter.h"
#include "GAS/ASC/PWAbilitySystemComponent.h"
#include "ProjectWTPS/Player/TPSPlayerState.h"

ATPSPlayerController::ATPSPlayerController()
{
	InputRouter = CreateDefaultSubobject<UPWInputRouter>("InputRouter");
}

void ATPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InputRouter->SetMappingContext(GetLocalPlayer());
	
	bShowMouseCursor = false;
}

void ATPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputRouter->BindAll(InputComponent);
	InputRouter->OnStarted.AddDynamic(this, &ThisClass::InputTagStarted);
	InputRouter->OnCompleted.AddDynamic(this, &ThisClass::InputTagCompleted);
}

void ATPSPlayerController::InputTagStarted(const FGameplayTag& InputTag)
{
	if (GetASC()) GetASC()->Input().AbilityInputTagPressed(InputTag);
}

void ATPSPlayerController::InputTagCompleted(const FGameplayTag& InputTag)
{
	if (GetASC()) GetASC()->Input().AbilityInputTagReleased(InputTag);
}

UPWAbilitySystemComponent* ATPSPlayerController::GetASC()
{
	if (!ASC)
		ASC = Cast<UPWAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPlayerState<ATPSPlayerState>()));
	return ASC;
}
