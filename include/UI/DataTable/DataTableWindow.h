//
// Created by Aashik on 03-07-2024.
//

#pragma once

#include <UI/UI.h>
#include <UI/DataTable/DataTable.h>
#include <UI/DataTable/DataTableMenu.h>
#include <UI/DataTable/DataTableQuery.h>
#include <UI/DataTable/DataTableFilter.h>

#include <State/DataTableWindowState.h>

class DataTableWindow final : public UI
{
public:
    explicit DataTableWindow(const std::shared_ptr<Data>& _data)
        : state(std::make_shared<DataTableWindowState>(_data)),
            dataTable(std::make_unique<DataTable>(state)), dataTableMenu(std::make_unique<DataTableMenu>(state)),
            dataTableQuery(std::make_unique<DataTableQuery>(state)), dataTableFilter(std::make_unique<DataTableFilter>(state))
    {}

    void onSetup() override;
    void onUpdate() override;
    void onKeyEvent() override;

private:
    // char loadingBuffer[256];

    bool enableClose = true;

    std::shared_ptr<DataTableWindowState> state;

    std::unique_ptr<DataTable> dataTable;
    std::unique_ptr<DataTableMenu> dataTableMenu;
    std::unique_ptr<DataTableQuery> dataTableQuery;
    std::unique_ptr<DataTableFilter> dataTableFilter;
};
