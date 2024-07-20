//
// Created by Aashik on 29-06-2024.
//

#pragma once

#include <iostream>

#include <gdal.h>
#include <gdal_priv.h>
#include <gdal_utils.h>

#include <Actor/Actor.h>
#include <Service/DataManagerService.h>

class DataManagerThread
{
public:
    void openData(const std::shared_ptr<Data>& data)
    {
        GDALDatasetH poDS = GDALOpenEx(data->input.path.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
        if (poDS == nullptr) {
            printf("Failed to open file.\n");
            return;
        }

        const std::string gpkg = Utils::currentDir() + "\\data\\" + data->id + ".gpkg";
        data->gpkg = gpkg;
        // std::cout << "Input : " << data->input.path << std::endl;
        // std::cout << "Output : " << gpkg << std::endl;

        std::vector<const char*> papszOptions;
        papszOptions.push_back("-f"); papszOptions.push_back("GPKG");
        papszOptions.push_back("-mapFieldType"); papszOptions.push_back("StringList=String(JSON)");
        papszOptions.push_back(nullptr);

        GDALVectorTranslateOptions *psOptions = GDALVectorTranslateOptionsNew(const_cast<char**>(papszOptions.data()), nullptr);
        GDALVectorTranslate(gpkg.c_str(), nullptr, 1, &poDS, psOptions, nullptr);

        GDALClose(poDS);
        GDALVectorTranslateOptionsFree(psOptions);
        data->release();
    }

};

class DataManagerService::Impl
{
public:
    Impl() : m_actor(std::make_shared<Actor<DataManagerThread>>()) {}

    std::shared_ptr<Actor<DataManagerThread>> actor()
    {
        return m_actor;
    }

    void openData(const std::shared_ptr<Data>& data)
    {
        actor()->invoke(&DataManagerThread::openData, std::move(data));
    }

private:
    std::shared_ptr<Actor<DataManagerThread>> m_actor;
};
