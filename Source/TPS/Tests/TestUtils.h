#pragma once
#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "Tests/AutomationCommon.h"
#include "Misc/OutputDeviceNull.h"

namespace TPS
{
namespace Test
{
template <typename T1, typename T2>
struct TestPayload
{
    T1 TestValue;
    T2 ExpectedValue;
    float Tolerance = KINDA_SMALL_NUMBER;
};

#define ENUM_LOOP_START(TYPE, EnumElem)                                        \
    for (int32 index = 0; index < StaticEnum<TYPE>()->NumEnums() - 1; ++index) \
    {                                                                          \
        const TYPE EnumElem = static_cast<TYPE>(index);
#define ENUM_LOOP_END }

template <typename T>
T* CreateBlueprint(UWorld* World, const FString& Name, const FTransform& Transform = FTransform::Identity)
{
    const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Name);
    return (World && Blueprint) ? World->SpawnActor<T>(Blueprint->GeneratedClass, Transform) : nullptr;
}

UWorld* GetTestGameWorld();
void CallFuncByNameWithParams(UObject* Object, const FString& FuncName, const TArray<FString>& Params);

class LevelScope
{
public:
    LevelScope(const FString MapName) { AutomationOpenMap(MapName); }
    ~LevelScope() { ADD_LATENT_AUTOMATION_COMMAND(FExitGameCommand); }
};

}  // namespace Test

}  // namespace TPS

#endif