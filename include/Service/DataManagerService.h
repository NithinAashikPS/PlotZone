//
// Created by Aashik on 29-06-2024.
//

#pragma once

#include <memory>

#include <Service/Service.h>
#include <Utils/Types.h>

class DataManagerService final : public Service
{
public:
    DataManagerService();
    ~DataManagerService() override;

    [[nodiscard]] std::shared_ptr<Data> openFile(const std::string&) const;

private:
    class Impl;
    const std::unique_ptr<Impl> impl;
};
