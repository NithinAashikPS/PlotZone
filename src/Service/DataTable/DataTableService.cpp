//
// Created by Aashik on 22-06-2024.
//

#include <algorithm>
#include <utility>
#include <Service/DataTableService.h>
#include "DataTableImpl.h"

DataTableService::DataTableService(const std::shared_ptr<Data>& data, const std::shared_ptr<Rows>& rows, const std::shared_ptr<Columns>& columns)
    : impl(std::make_unique<Impl>(data, rows, columns)) {}

void DataTableService::reload() const { impl->reload(); }

void DataTableService::insertRow() const { impl->insertRow(); }

void DataTableService::insertColumn(const int index) const
{
    // impl->actor()->invoke(&SpreadSheetThread::insertColumn, index);
}

void DataTableService::deleteRow(const int index) const { impl->deleteRow(index); }

void DataTableService::deleteRows(RowIdxs rowIdxs) const { impl->deleteRows(std::move(rowIdxs)); }

void DataTableService::deleteColumn(const int index) const { impl->deleteColumn(index); }

void DataTableService::updateCell(const int row, const int col, const std::string& value) const
{
    impl->updateCell(row, col, value);
}