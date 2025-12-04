// copyright mkurtt96


#include "ProjectWTPS/Player/TPSPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "PWInputRouter.h"
#include "GAS/ASC/PWAbilitySystemComponent.h"
#include "ProjectWTPS/Player/TPSPlayerState.h"
#include "ProjectWTPS/Settings/GameSettings.h"

ATPSPlayerController::ATPSPlayerController()
{
	InputRouter = CreateDefaultSubobject<UPWInputRouter>("InputRouter");
}

void ATPSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = false;
}

void ATPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputRouter->InputConfig = UGameSettings::Get()->GetInputConfig();
	InputRouter->SetMappingContext(GetLocalPlayer());
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
