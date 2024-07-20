//
// Created by Aashik on 07-07-2024.
//

#pragma once

#include <memory>

#include <Utils/Types.h>

#include <Service/DataTableService.h>

class DataTableWindowState
{
public:
    explicit DataTableWindowState(const std::shared_ptr<Data>& _data) : data(_data)
    {
        service = new DataTableService(data, rows, columns);
    }
    bool enableEditing = false;
    std::shared_ptr<Data> data;
    RowIdxs selectedRows;
    DataTableService* service;
    std::shared_ptr<Rows> rows = std::make_shared<Rows>();
    std::shared_ptr<Columns> columns = std::make_shared<Columns>();
};
