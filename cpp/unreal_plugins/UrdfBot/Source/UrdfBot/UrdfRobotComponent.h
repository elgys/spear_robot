//
// Copyright(c) 2022 Intel. Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//

#pragma once

#include <map>
#include <string>
#include <vector>

#include <CoreMinimal.h>
#include <Components/SceneComponent.h>

#include "UrdfRobotComponent.generated.h"

class UUrdfJointComponent;
class UUrdfLinkComponent;
struct Box;
struct UrdfLinkDesc;
struct UrdfRobotDesc;

UCLASS()
class URDFBOT_API UUrdfRobotComponent : public USceneComponent
{
    GENERATED_BODY()
public:
    UUrdfRobotComponent();
    ~UUrdfRobotComponent();

    void createChildComponents(UrdfRobotDesc* robot_desc);

    // Agent interface used by UrdfBotAgent
    std::map<std::string, Box> getActionSpace(const std::vector<std::string>& action_components) const;
    std::map<std::string, Box> getObservationSpace(const std::vector<std::string>& observation_components) const;
    void applyAction(const std::map<std::string, std::vector<uint8_t>>& action);
    std::map<std::string, std::vector<uint8_t>> getObservation(const std::vector<std::string>& observation_components) const;

    // Pawn interface used by UrdfBotPawn
    void applyAction(std::map<std::string, float> action);
    void addAction(std::map<std::string, float> action);

    UUrdfLinkComponent* root_link_component_ = nullptr;
    std::map<std::string, UUrdfLinkComponent*> link_components_;
    std::map<std::string, UUrdfJointComponent*> joint_components_;

private:
    void createChildComponents(UrdfLinkDesc* parent_link_desc, UUrdfLinkComponent* parent_link);
};
