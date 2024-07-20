//
// Created by Aashik on 02-07-2024.
//

#pragma once

#include <string>
#include <vector>
#include <memory>

#include <UI/UI.h>
#include <State/DataTableWindowState.h>

using ComboItem = std::vector<std::string>;

class DataTableFilter final : public UI
{
public:
    explicit DataTableFilter(const std::shared_ptr<DataTableWindowState>& _state) : state(_state) {}

    void onSetup() override;
    void onUpdate() override;

private:
    std::shared_ptr<DataTableWindowState> state;

    ComboItem comboItems;
    char* currentComboItem = nullptr;
    std::string currentComboPreviewText;

    float comboBoxWidth = 0.0f;

};
