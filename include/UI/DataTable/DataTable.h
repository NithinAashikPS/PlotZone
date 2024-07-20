//
// Created by Aashik on 22-06-2024.
//

#pragma once

#include <functional>

#include <imgui.h>
#include <memory>

#include <UI/UI.h>

#include <State/DataTableWindowState.h>

class DataTableKeyEvent
{
public:
    static bool shiftPressed;
    static bool ctrlPressed;
    static bool homePressed;
    static bool endPressed;
};

using CallBack = std::function<void()>;

class DataTable final : public UI
{
public:
    explicit DataTable(const std::shared_ptr<DataTableWindowState>& _state) : state(_state) {}

    void onSetup() override;
    void onUpdate() override;
    void onKeyEvent() override;

private:
    void renderRightClickMenu() const;
    void renderColumns() const;
    void renderRows();

    static void deDecorateCell(const CallBack&);
    void selectRow(int);
    void deselectRow();

    [[nodiscard]] ImVec2 getSelectPos(const int&) const;

    float colSize = 0.0f;
    int tableFlags{};
    int cellFlags{};
    int columnFlags{};
    ImGuiListClipper clipper;

    std::shared_ptr<DataTableWindowState> state;
};
