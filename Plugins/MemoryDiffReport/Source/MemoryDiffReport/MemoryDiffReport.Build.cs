// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class MemoryDiffReport : ModuleRules
{
	public MemoryDiffReport(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
        {

            string BinariesDir = Path.Combine(ModuleDirectory, "../../Binaries", Target.Platform.ToString());
            string ProjectBinaries = Path.Combine(ModuleDirectory, "../../../../Binaries", Target.Platform.ToString());
            RuntimeDependencies.Add(Path.Combine(BinariesDir, "MemoryReport.exe"));
            if (!Directory.Exists(BinariesDir))
            {
                Directory.CreateDirectory(BinariesDir);

            }
            if (!Directory.Exists(ProjectBinaries))
            {
                Directory.CreateDirectory(ProjectBinaries);

            }
            try
            {
               
                    File.Copy(Path.Combine(BinariesDir, "MemoryReport.exe"), Path.Combine(ProjectBinaries, "MemoryReport.exe"));

              

            }
            catch (Exception e)
            {

                System.Console.WriteLine("copy MemoryReport.exe exception,maybe have exists", e.ToString());
            }

        }
            PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
