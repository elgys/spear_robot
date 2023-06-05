//
// Copyright(c) 2022 Intel. Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//

#include "REA/REA.h"

#include <iostream>

#include "CoreUtils/Assert.h"

void REA::StartupModule()
{
    std::cout << "[SPEAR | REA.cpp] REA::StartupModule" << std::endl;

    ASSERT(FModuleManager::Get().IsModuleLoaded(TEXT("CoreUtils")));
}

void REA::ShutdownModule()
{
    std::cout << "[SPEAR | REA.cpp] REA::ShutdownModule" << std::endl;    
}

IMPLEMENT_MODULE(REA, REA)
