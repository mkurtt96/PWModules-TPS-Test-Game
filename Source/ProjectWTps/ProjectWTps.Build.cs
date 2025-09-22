// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectWTps : ModuleRules
{
	public ProjectWTps(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate", "PWContracts"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ProjectWTps",
			"ProjectWTps/Variant_Platforming",
			"ProjectWTps/Variant_Platforming/Animation",
			"ProjectWTps/Variant_SideScrolling",
			"ProjectWTps/Variant_SideScrolling/AI",
			"ProjectWTps/Variant_SideScrolling/Gameplay",
			"ProjectWTps/Variant_SideScrolling/Interfaces",
			"ProjectWTps/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
