//
// Copyright(c) 2022 Intel. Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "SimulationController/Agent.h"

class AActor;
class ARecastNavMesh;
class UNavigationSystemV1;
class UWorld;

class AREApawn;
class CameraSensor;
class ImuSensor;
struct Box;

class REAAgent : public Agent
{
public:
    REAAgent(UWorld* world);
    ~REAAgent();

    void findObjectReferences(UWorld* world) override;
    void cleanUpObjectReferences() override;

    std::map<std::string, Box> getActionSpace() const override;
    std::map<std::string, Box> getObservationSpace() const override;
    std::map<std::string, Box> getStepInfoSpace() const override;

    void applyAction(const std::map<std::string, std::vector<uint8_t>>& action) override;
    std::map<std::string, std::vector<uint8_t>> getObservation() const override;
    std::map<std::string, std::vector<uint8_t>> getStepInfo() const override;

    void reset() override;
    bool isReady() const override;

private:
    void buildNavMesh();
    void generateTrajectoryToGoal();

    AREApawn* REA_pawn_ = nullptr;
    AActor* goal_actor_ = nullptr;

    UNavigationSystemV1* nav_sys_ = nullptr;
    ARecastNavMesh* nav_mesh_ = nullptr;

    std::unique_ptr<CameraSensor> camera_sensor_;
    std::unique_ptr<ImuSensor> imu_sensor_;

    std::vector<float> trajectory_;
};
