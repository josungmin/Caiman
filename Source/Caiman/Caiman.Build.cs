// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Caiman : ModuleRules
{
	public Caiman(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { "Caiman" });

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			// Defualt Module
			"Core", 
			"CoreUObject", 
			"Engine",

			// New Module
			"InputCore",
			"EnhancedInput",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
