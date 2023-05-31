// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class REA : ModuleRules
{
	public REA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.Default;
		bUseUnity = false;

		OptimizeCode = ModuleRules.CodeOptimization.InShippingBuildsOnly;

		// Our ASSERT macro throws exceptions, and so does our templated function Config::get(...),
		// because it depends on yaml-cpp, which throws exceptions. So we need to enable exceptions
		// everywhere.
		bEnableExceptions = true;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "CoreUtils", "Engine", "PhysX", "PhysXVehicleLib", "PhysXVehicles" });
        PrivateDependencyModuleNames.AddRange(new string[] { });

        //
        // Eigen
        //

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "libeigen", "BUILD", "Win64", "include", "eigen3"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "libeigen", "BUILD", "Mac", "include", "eigen3"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "libeigen", "BUILD", "Linux", "include", "eigen3"));
        }
        else
        {
            throw new Exception("[SPEAR | OpenBot.Build.cs] Unexpected: Target.Platform == " + Target.Platform);
        }
    }
}
