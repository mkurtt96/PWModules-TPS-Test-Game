// Copyright Epic Games, Inc. All Rights Reserved.


#include "Public/Animation/AnimNotify_CheckCombo.h"

#include "Components/SkeletalMeshComponent.h"
#include "Public/Interfaces/CombatAttacker.h"

void UAnimNotify_CheckCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	// cast the owner to the attacker interface
	if (ICombatAttacker* AttackerInterface = Cast<ICombatAttacker>(MeshComp->GetOwner()))
	{
		// tell the actor to check for combo string
		AttackerInterface->CheckCombo();
	}
}

FString UAnimNotify_CheckCombo::GetNotifyName_Implementation() const
{
	return FString("Check Combo String");
}
