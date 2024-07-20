//
// Created by Aashik on 22-06-2024.
//

#include <algorithm>
#include <iostream>
#include <string>

#include <imgui_internal.h>

#include <UI/DataTable/DataTable.h>
#include <UI/DataTable/DataTableWindow.h>

bool DataTableKeyEvent::shiftPressed = false;
bool DataTableKeyEvent::ctrlPressed = false;
bool DataTableKeyEvent::homePressed = false;
bool DataTableKeyEvent::endPressed = false;

void DataTable::onSetup()
{
    tableFlags |= ImGuiTableFlags_RowBg | ImGuiTableFlags_NoPadOuterX | ImGuiTableFlags_Hideable |
        ImGuiTableFlags_NoPadInnerX | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable |
        ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuterH;
    cellFlags |= ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_AutoSelectAll;
    columnFlags |= ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize;
}

void DataTable::onUpdate()
{
    const float offset = state->enableEditing ? 3*33 : 2*33;
    ImGui::BeginChild(("Table##" + state->data->id).c_str(), ImVec2 {ImGui::GetWindowSize().x, ImGui::GetWindowHeight() - ImGui::GetFrameHeight() - offset});

    if (state->columns->empty())
    {
        ImGui::EndChild();
        return;
    }

    colSize = ImGui::CalcTextSize(std::to_string(state->rows->size()).c_str()).x + 13.0f;
    if (ImGui::BeginTable(state->data->input.name.c_str(), static_cast<int>(state->columns->size()), tableFlags))
    {
        ImGui::TableSetupScrollFreeze(1, 1);

        ImGuiStyle& style = ImGui::GetStyle();
        const ImVec2 old_padding = style.CellPadding;
        style.CellPadding = ImVec2(50.0f, 5.0f);

        renderColumns();
        style.CellPadding = ImVec2(50.0f, 1.0f);
        if (DataTableKeyEvent::homePressed)
            ImGui::SetScrollHereY(1.0f);
        renderRows();
        if (DataTableKeyEvent::endPressed)
            ImGui::SetScrollHereY(1.0f);
        style.CellPadding = old_padding;
        ImGui::EndTable();
    }
    ImGui::EndChild();

}

void DataTable::onKeyEvent()
{
    DataTableKeyEvent::shiftPressed = ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift);
    DataTableKeyEvent::ctrlPressed = ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl);
    DataTableKeyEvent::homePressed = ImGui::IsKeyDown(ImGuiKey_Home);
    DataTableKeyEvent::endPressed = ImGui::IsKeyDown(ImGuiKey_End);


    if (DataTableKeyEvent::ctrlPressed && ImGui::IsKeyDown(ImGuiKey_G))
    {

    }
}

void DataTable::deDecorateCell(const CallBack& callBack)
{
    ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 0, 0, 0));
    callBack();
    ImGui::PopStyleColor(3);
}

void DataTable::renderRightClickMenu() const
{
    const ImGuiTable* table = ImGui::GetCurrentTable();

    if (ImGui::BeginPopupContextItem())
    {

        if (ImGui::MenuItem("Insert Column", "Ctrl+Shift+C", false, table->CurrentColumn))
            state->service->insertColumn(table->CurrentColumn - 1);

        if (ImGui::MenuItem("Delete Column", nullptr, false, table->CurrentColumn))
            state->service->deleteColumn(table->CurrentColumn);

        ImGui::EndPopup();
    }
}

void DataTable::renderColumns() const
{
    ImGui::TableSetupColumn(
        "Id",  columnFlags | ImGuiTableColumnFlags_NoReorder | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoHeaderLabel,
        colSize);
    for (auto& column : *state->columns)
    {
        if (column == "fid")
            continue;
        ImGui::TableSetupColumn(column.c_str());
    }
    ImGui::TableHeadersRow();
}

void DataTable::renderRows()
{
    clipper.Begin(static_cast<int>(state->rows->size()), 23.5f);
    while (clipper.Step())
    {
        for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
        {
            ImGui::TableNextRow(ImGuiTableRowFlags_None, 5.0f);
            ImGui::TableSetColumnIndex(0);

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2 {0.0f, 2.5f});
            ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, getSelectPos(row));
            if (ImGui::Selectable(std::to_string(row).c_str(),
                                  std::ranges::find(state->selectedRows, row) != state->selectedRows.end() && state->enableEditing,
                                  ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap, ImVec2 {0.0f, 20.0f}))
            {
                selectRow(row);
            }
            ImGui::PopStyleVar();
            // renderRightClickMenu();

            for (int col = 1; col < static_cast<int>(state->columns->size()); ++col)
            {
                ImGui::TableSetColumnIndex(col);
                ImGui::SetNextItemWidth(ImGui::GetColumnWidth(col));
                char cellId[32];
                snprintf(cellId, sizeof(cellId), "##cell_%d_%d", row, col);

                if (state->enableEditing)
                {
                    char buffer[256];
                    strncpy(buffer, (*state->rows)[row][col].c_str(), sizeof(buffer));

                    deDecorateCell([&]()
                    {
                        if (ImGui::InputText(cellId, buffer, sizeof(buffer), cellFlags | ImGuiInputTextFlags_EnterReturnsTrue))
                        {
                            state->service->updateCell(row, col, std::string(buffer));
                        }
                    });
                } else
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2 {0.0f, 0.5f});
                    ImGui::Selectable((*state->rows)[row][col].c_str(), false, ImGuiSelectableFlags_AllowOverlap, ImVec2 {0.0f, 21.0f});
                    ImGui::PopStyleVar();
                }

                // renderRightClickMenu();
            }
            ImGui::PopStyleVar();
        }
    }
}

ImVec2 DataTable::getSelectPos(const int& row) const
{
    static float _colSize = ImGui::CalcTextSize(std::to_string(row).c_str()).x;
    return ImVec2 {_colSize/ImGui::GetWindowSize().x, 0.5f};
}

void DataTable::selectRow(const int row)
{
    if (DataTableKeyEvent::shiftPressed)
    {
        const int lastItem = state->selectedRows.at(state->selectedRows.size() - 1);
        for (int i = row; i != lastItem; i += row < lastItem ? 1 : -1)
        {
            state->selectedRows.emplace_back(i);
        }
        return;
    }
    if (DataTableKeyEvent::ctrlPressed)
    {
        state->selectedRows.emplace_back(row);
        return;
    }

    if (std::ranges::find(state->selectedRows, row) == state->selectedRows.end())
    {
        deselectRow();
        state->selectedRows.emplace_back(row);
    }
    else
        deselectRow();
}

void DataTable::deselectRow()
{
    state->selectedRows.clear();
}
