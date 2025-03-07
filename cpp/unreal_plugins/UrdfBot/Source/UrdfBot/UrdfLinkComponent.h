//
// Copyright(c) 2022 Intel. Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//

#pragma once

#include <CoreMinimal.h>
#include <Components/StaticMeshComponent.h>

#include "UrdfLinkComponent.generated.h"

class UUrdfJointComponent;
struct UrdfLinkDesc;

UCLASS()
class URDFBOT_API UUrdfLinkComponent : public UStaticMeshComponent
{
    GENERATED_BODY()
public:
    // UStaticMeshComponent interface
    void BeginPlay() override;

    void initializeComponent(UrdfLinkDesc* link_desc);

    float mass_;
    FVector relative_scale_;
};
