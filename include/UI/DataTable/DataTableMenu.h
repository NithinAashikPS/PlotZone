//
// Created by Aashik on 02-07-2024.
//

#pragma once

#include <memory>

#include <UI/UI.h>

#include <Service/DataTableService.h>

#include <State/DataTableWindowState.h>

// class DataTableState;
struct MenuState
{
    bool disableAdd = true;
    bool disableDelete = true;
    bool disableCut = true;
    bool disableCopy = true;
    bool disablePaste = true;

    bool disableSelectAll = true;
    bool disableInverseSelect = true;
    bool disableDeSelect = true;

    bool disableMap = true;
    bool disableAddColumn = true;
};

class DataTableMenu final : public UI
{
public:
    explicit DataTableMenu(const std::shared_ptr<DataTableWindowState>& _state) : state(_state) {}

    void onSetup() override;
    void onUpdate() override;
    void onKeyEvent() override;

private:
    void selectAll() const;
    void deselect() const;
    void inverseSelect();

    void insertRow() const;
    void deleteRow() const;

    void updateMenuState();

    std::shared_ptr<DataTableWindowState> state;
    RowIdxs inverseSelectIdx;
    MenuState menuState;
    ImVec4 oldColor;
    bool popStyle = false;
};
