//
// Created by Aashik on 29-06-2024.
//

#include <gdal.h>

#include <Utils/Utils.h>
#include <Service/DataManagerService.h>

#include "DataManagerImpl.h"

DataManagerService::DataManagerService() : impl(std::make_unique<Impl>())
{
    GDALAllRegister();
    OGRRegisterAll();
}

DataManagerService::~DataManagerService()
{
    GDALDestroyDriverManager();
}

std::shared_ptr<Data> DataManagerService::openFile(const std::string& filePath) const
{
    auto data = std::make_shared<Data>();
    data->id = Utils::UUID();
    data->input.name = Utils::fileName(filePath);
    data->input.extension = Utils::fileExtension(filePath);
    data->input.path = filePath;
    impl->openData(data);
    return data;
}
