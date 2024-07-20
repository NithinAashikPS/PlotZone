//
// Created by Aashik on 22-06-2024.
//

#pragma once

#include <gdal.h>
#include <iostream>
#include <string>
#include <utility>


#include <spatialite/sqlite.h>

#include <Utils/Thread.h>
#include <Service/DataTableService.h>

#include "DataTableQuery.h"

using ExeQuery = std::function<void()>;
using UpdateData = std::function<void()>;

struct  DataTableContext
{
    std::string tableName;
    std::shared_ptr<Rows> rows = std::make_shared<Rows>();
    std::shared_ptr<Columns> columns = std::make_shared<Columns>();
};

class DataTableThread
{
public:
    explicit DataTableThread(const std::shared_ptr<Data>& _data, const std::shared_ptr<Rows>& _rows, const std::shared_ptr<Columns>& _columns)
        : data(_data), ui_rows(_rows), ui_columns(_columns)
    {
        data->wait();
        loadAllData();
    }

    void reload(void*) { loadAllData(); }

    void insertRow(void*)
    {
        openDatabase([&]()
        {
            char query[256];
            snprintf(query, sizeof(query), DataTableQuery::EmptyRow.c_str(), context.tableName.c_str());
            sqlite3_exec(db, std::string(query).c_str(), nullptr, nullptr, nullptr);
        });
        updateRowData([&]()
        {
            context.rows->emplace_back(static_cast<int>(ui_columns->size()), "");
            context.rows->at(context.rows->size()-1)[0] = std::to_string(context.rows->size());
        });
    }

    void insertColumn(const int index)
    {
    }

    void deleteRow(const int index)
    {
        deleteRowFromDb(index);
        updateRowData([&]()
        {
            context.rows->erase(context.rows->begin() + index);
        });
    }

    void deleteRows(RowIdxs rowIdxs)
    {
        updateRowData([&]()
        {
            std::ranges::sort(rowIdxs, std::greater<int>());
            for (const auto& index : rowIdxs) {
                if (index >= 0 && index < context.rows->size()) {
                    deleteRowFromDb(index);
                    context.rows->erase(context.rows->begin() + index);
                }
            }
        });
    }

    void deleteColumn(const int index)
    {
        openDatabase([&]()
        {
            char query[256];
            snprintf(query, sizeof(query), DataTableQuery::DeleteColumn.c_str(), context.tableName.c_str(), ui_columns->at(index).c_str());
            sqlite3_exec(db, std::string(query).c_str(), nullptr, nullptr, nullptr);
        });
        loadAllData();
    }

    void updateCell(const int row, const int col, const std::string& value)
    {
        updateRowData([&]()
        {
            (*context.rows)[row][col] = value;
        });
    }

private:
    void updateRowData(const UpdateData& updateData)
    {
        *context.rows = *ui_rows;
        if (updateData)
            updateData();
        *ui_rows = std::move(*context.rows);
    }

    void updateColumnData(const UpdateData& updateData) const
    {
        *context.columns = *ui_columns;
        if (updateData)
            updateData();
        *ui_columns = std::move(*context.columns);
    }

    void deleteRowFromDb(const int& index)
    {
        openDatabase([&]()
        {
            char query[256];
            snprintf(query, sizeof(query), DataTableQuery::DeleteRow.c_str(), context.tableName.c_str());
            sqlite3_stmt *stmt;
            sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
            sqlite3_bind_int(stmt, 1, std::stoi(ui_rows->at(index).at(0)));
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        });
    }

    void openDatabase(const ExeQuery& execQuery)
    {
        if(!sqlite3_open(data->gpkg.c_str(), &db)) {
            sqlite3_enable_load_extension(db, 1);
            sqlite3_load_extension(db, "mod_spatialite", nullptr, nullptr);

            if (execQuery)
                execQuery();
            sqlite3_close(db);
        }
    }

    void loadAllData()
    {
        openDatabase([&]()
        {
            sqlite3_exec(db, DataTableQuery::TableName.c_str(), &DataTableThread::TableName, &context, nullptr);
            if (context.tableName.empty())
                return;

            char query[256];
            snprintf(query, sizeof(query), DataTableQuery::ColumnName.c_str(), context.tableName.c_str());
            sqlite3_exec(db, std::string(query).c_str(), &DataTableThread::ColumnName, &context, nullptr);

            snprintf(query, sizeof(query), DataTableQuery::SelectAll.c_str(), context.tableName.c_str());
            sqlite3_exec(db, std::string(query).c_str(), &DataTableThread::SelectAll, &context, nullptr);
        });
        *ui_columns = std::move(*context.columns);
        *ui_rows = std::move(*context.rows);
    }

    static int TableName(void* data, const int argc, char **argv, char **)
    {
        auto* context = static_cast<DataTableContext*>(data);
        if (argc > 0)
            context->tableName = argv[0];
        return 0;
    }

    static int ColumnName(void* data, const int argc, char **argv, char **)
    {
        const auto* context = static_cast<DataTableContext*>(data);
        if (std::string(argv[argc-1]) != "geom")
            context->columns->emplace_back(argv[argc-1]);
        return 0;
    }

    static int SelectAll(void* data, const int argc, char **argv, char **azColName)
    {
        const auto* context = static_cast<DataTableContext*>(data);
        Columns _column;
        for(int i = 0; i<argc; i++)
            if (std::string(azColName[i]) != "geom")
                _column.emplace_back(argv[i] ? argv[i] : "");

        context->rows->emplace_back(_column);
        return 0;
    }

    DataTableContext context;
    sqlite3 *db;

    std::shared_ptr<Data> data;
    std::shared_ptr<Rows> ui_rows;
    std::shared_ptr<Columns> ui_columns;
};

class DataTableService::Impl
{
public:
    Impl(const std::shared_ptr<Data>& _data, const std::shared_ptr<Rows>& _rows, const std::shared_ptr<Columns>& _columns)
        : thread(std::make_unique<Thread<DataTableThread>>(_data, _rows, _columns)) {}

    std::shared_ptr<Actor<DataTableThread>> actor()
    {
        return thread->actor();
    }

    void reload()
    {
        actor()->invoke(&DataTableThread::reload, nullptr);
    }

    void insertRow()
    {
        actor()->invoke(&DataTableThread::insertRow, nullptr);
    }

    void deleteRow(int index)
    {
        actor()->invoke(&DataTableThread::deleteRow, std::move(index));
    }

    void deleteColumn(int index)
    {
        actor()->invoke(&DataTableThread::deleteColumn, std::move(index));
    }

    void deleteRows(RowIdxs rowIdxs)
    {
        actor()->invoke(&DataTableThread::deleteRows, std::move(rowIdxs));
    }

    void updateCell(int row, int col, const std::string& value)
    {
        actor()->invoke(&DataTableThread::updateCell, std::move(row), std::move(col), std::move(value));
    }

private:
    // std::shared_ptr<Actor<DataTableThread>> m_actor;
    std::unique_ptr<Thread<DataTableThread>> thread;
};
