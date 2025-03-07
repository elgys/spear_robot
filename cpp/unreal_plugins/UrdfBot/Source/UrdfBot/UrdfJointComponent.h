//
// Copyright(c) 2022 Intel. Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//

#pragma once

#include <CoreMinimal.h>
#include <PhysicsEngine/PhysicsConstraintComponent.h>

#include "UrdfJointComponent.generated.h"

class UUrdfLinkComponent;
enum class UrdfJointControlType;
enum class UrdfJointType;
struct UrdfJointDesc;

UCLASS()
class URDFBOT_API UUrdfJointComponent : public UPhysicsConstraintComponent
{
    GENERATED_BODY()
public:
    // UPhysicsConstraintComponent interface
    void BeginPlay() override;

    void initializeComponent(UrdfJointDesc* joint_desc, UUrdfLinkComponent* parent_link, UUrdfLinkComponent* child_link);

    void applyAction(float action);
    void addAction(float action);

    UUrdfLinkComponent* parent_link_component_;
    UUrdfLinkComponent* child_link_component_;

    UrdfJointType joint_type_;
    UrdfJointControlType control_type_;
};
