// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyMemoryProjectClientTarget : TargetRules
{
	public MyMemoryProjectClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;
		ExtraModuleNames.Add("MyMemoryProject");
	}
}
