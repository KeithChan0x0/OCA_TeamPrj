// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OCA_TeamPrj : ModuleRules
{
	public OCA_TeamPrj(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
