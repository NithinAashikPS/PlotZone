//
// Created by Aashik on 29-06-2024.
//

#pragma once

#include <memory>
#include <Service/DataManagerService.h>

class ServiceLocator {
public:
    static DataManagerService* getDataManager() {
        return dataManager;
    }

    static void provide(DataManagerService* dm) {
        dataManager = dm;
    }

private:
    static DataManagerService* dataManager;
};

DataManagerService* ServiceLocator::dataManager = nullptr;
