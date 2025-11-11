     using UnrealBuildTool;
 
     public class K2NodeModule: ModuleRules
     {
        public K2NodeModule(ReadOnlyTargetRules Target) : base(Target)
        {
            PublicDependencyModuleNames.AddRange(new string[]{
                "Core",
                "CoreUObject",
                "Engine"
            });
            PrivateDependencyModuleNames.AddRange(new string[]{
            "BlueprintGraph",
            "GraphEditor",
            "KismetCompiler",
            "SlateCore",
            "UnrealEd"
        });
        }
    }