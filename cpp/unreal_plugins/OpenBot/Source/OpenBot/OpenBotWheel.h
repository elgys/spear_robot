//
// Copyright(c) 2022 Intel. Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//

#pragma once

#include <CoreMinimal.h>
#include <VehicleWheel.h>

#include "CoreUtils/SuppressCompilerWarnings.h"

#include "OpenBotWheel.generated.h"

// We need to wrap this entire class with BEGIN_SUPPRESS_COMPILER_WARNINGS/END_SUPPRESS_COMPILER_WARNINGS
// because it inherits from a deprecated class that interacts with Unreal's code generation functionality.
BEGIN_SUPPRESS_COMPILER_WARNINGS
UCLASS()
class UOpenBotWheel : public UVehicleWheel
{
    GENERATED_BODY()
public:
    UOpenBotWheel();
    ~UOpenBotWheel();
};
END_SUPPRESS_COMPILER_WARNINGS
