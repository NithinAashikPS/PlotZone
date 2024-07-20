//
// Created by Aashik on 22-06-2024.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <Service/Service.h>
#include <Utils/Types.h>

using Columns = std::vector<std::string>;
using Rows = std::vector<Columns>;

using RowIdxs = std::vector<int>;

class DataTableService final : public Service
{
public:
    DataTableService(const std::shared_ptr<Data>&, const std::shared_ptr<Rows>&, const std::shared_ptr<Columns>&);

    void reload() const;
    void insertRow() const;
    void insertColumn(int) const;
    void deleteRow(int) const;
    void deleteRows(RowIdxs) const;
    void deleteColumn(int) const;
    void updateCell(int, int, const std::string&) const;

private:
    class Impl;
    const std::unique_ptr<Impl> impl;
};
