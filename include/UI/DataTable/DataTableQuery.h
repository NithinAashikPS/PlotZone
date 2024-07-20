//
// Created by Aashik on 02-07-2024.
//

#pragma once

#include <memory>

#include <UI/UI.h>
#include <State/DataTableWindowState.h>


class DataTableQuery final : public UI
{
public:
    explicit DataTableQuery(const std::shared_ptr<DataTableWindowState>& _state) : state(_state) {}

    void onSetup() override;
    void onUpdate() override;

private:
    std::shared_ptr<DataTableWindowState> state;
};
