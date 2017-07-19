// Copyright (c) 2015 Jussi Saarivirta 2016 conflict.industries MIT License (MIT)

using UnrealBuildTool;

public class DatabaseSQLite : ModuleRules
{
  public DatabaseSQLite(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePaths.AddRange(
      new string[] {
        "DatabaseSQLite/Public"
      }
    );

    PrivateIncludePaths.AddRange(
      new string[] {
        "DatabaseSQLite/Private"
      }
    );

    PublicDependencyModuleNames.AddRange(
      new string[] {
        "Engine",
        "Core",
        "CoreUObject"
      }
    );

    PrivateDependencyModuleNames.AddRange(
      new string[] {}
    );

    DynamicallyLoadedModuleNames.AddRange(
      new string[] {}
    );
  }
}
