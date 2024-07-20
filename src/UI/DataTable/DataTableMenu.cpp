//
// Created by Aashik on 02-07-2024.
//

#include <imgui.h>
#include <imgui_internal.h>
#include <numeric>
#include <UI/DataTable/DataTableMenu.h>

#include <Utils/Icons.h>

#include <UI/DataTable/DataTableWindow.h>


void DataTableMenu::onSetup() {}

void DataTableMenu::onUpdate()
{
    updateMenuState();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 {3.0f, 3.5f});
    ImGui::BeginChild(("TableMenu##" + state->data->id).c_str(), ImVec2 {ImGui::GetWindowSize().x, 30.0f}, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoScrollbar);
    ImGui::PopStyleVar();

    oldColor = ImGui::GetStyle().Colors[ImGuiCol_Button];

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2 {0.0f, 0.0f});
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.0f, 0.0f, 0.0f, 0.0f});
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4 {0.0f, 0.0f, 0.0f, 0.5f});

    if (state->enableEditing) {ImGui::PushStyleColor(ImGuiCol_Button, oldColor); popStyle = true;}
    ImGui::Button(ICON_MD_EDIT, ImVec2 {24.0f, 24.0f}); ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Toggle editing mode\t(Ctrl+E)"); }
    if (ImGui::IsItemClicked()) { state->enableEditing =! state->enableEditing; deselect();}
    if (popStyle) { ImGui::PopStyleColor(); popStyle=false; }

    ImGui::Button(ICON_MD_SAVE, ImVec2 {24.0f, 24.0f}); ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Save edits\t(Ctrl+S)"); }

    if (ImGui::Button(ICON_MD_REFRESH, ImVec2 {24.0f, 24.0f})) { insertRow(); } ImGui::SameLine(0.0f, 9.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Refresh table\t(F5)"); }

    ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 1.0f); ImGui::SameLine(0.0f, 9.0f);

    ImGui::BeginDisabled(menuState.disableAdd);
    if (ImGui::Button(ICON_MD_ADD_BOX, ImVec2 {24.0f, 24.0f})) { state->service->insertRow(); } ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Add feature"); }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(menuState.disableDelete);
    if (ImGui::Button(ICON_MD_DELETE, ImVec2 {24.0f, 24.0f})) { deleteRow(); } ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Delete selected rows/columns\t(Del)"); }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(menuState.disableCut);
    ImGui::Button(ICON_MD_CONTENT_CUT, ImVec2 {24.0f, 24.0f}); ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Cut selected rows to clipboard\t(Ctrl+X)"); }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(menuState.disableCopy);
    ImGui::Button(ICON_MD_CONTENT_COPY, ImVec2 {24.0f, 24.0f}); ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Copy selected rows to clipboard\t(Ctrl+C)"); }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(menuState.disablePaste);
    ImGui::Button(ICON_MD_CONTENT_PASTE, ImVec2 {24.0f, 24.0f}); ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Paste rows from clipboard\t(Ctrl+V)"); }
    ImGui::EndDisabled();

    ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 1.0f); ImGui::SameLine(0.0f, 9.0f);

    ImGui::Button(ICON_MD_FUNCTIONS, ImVec2 {24.0f, 24.0f}); ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Select rows using expression"); }

    ImGui::BeginDisabled(menuState.disableSelectAll);
    if (ImGui::Button(ICON_MD_SELECT_ALL, ImVec2 {24.0f, 24.0f})) { selectAll(); } ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Select all\t(Ctrl+A)"); }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(menuState.disableInverseSelect);
    if (ImGui::Button(ICON_MD_PHOTO_SIZE_SELECT_SMALL, ImVec2 {24.0f, 24.0f})) { inverseSelect(); } ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Invert selection\t(Ctrl+R)"); }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(menuState.disableDeSelect);
    if (ImGui::Button(ICON_MD_DESELECT, ImVec2 {24.0f, 24.0f})) { deselect(); } ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Deselect all rows from the layer\t(Ctrl+Shift+A)"); }
    ImGui::EndDisabled();

    ImGui::Button(ICON_MD_FILTER_ALT, ImVec2 {24.0f, 24.0f}); ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Select/filter rows using form\t(Ctrl+F)"); }

    ImGui::BeginDisabled(menuState.disableMap);
    ImGui::Button(ICON_MD_MAP, ImVec2 {24.0f, 24.0f}); ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("Edit geometry\t(Ctrl+G)"); }
    ImGui::EndDisabled();

    ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 1.0f); ImGui::SameLine(0.0f, 9.0f);

    ImGui::BeginDisabled(menuState.disableAddColumn);
    ImGui::Button(ICON_MD_VIEW_COLUMN, ImVec2 {24.0f, 24.0f}); ImGui::SameLine(0.0f, 4.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) { ImGui::SetTooltip("New column\t(Ctrl+W)"); }
    ImGui::EndDisabled();

    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(2);

    ImGui::EndChild();
}

void DataTableMenu::onKeyEvent()
{
    if (ImGui::IsKeyDown(ImGuiKey_Delete))
    {
        state->service->deleteRows(state->selectedRows);
    }
}

void DataTableMenu::updateMenuState()
{
    menuState.disableAdd = !state->enableEditing;
    menuState.disableDelete = state->selectedRows.empty() || !state->enableEditing;
    menuState.disableCut = state->selectedRows.empty() || !state->enableEditing;
    menuState.disableCopy = state->selectedRows.empty() || !state->enableEditing;

    menuState.disableSelectAll = state->selectedRows.size() == state->rows->size() || !state->enableEditing;
    menuState.disableInverseSelect = state->selectedRows.empty() || menuState.disableSelectAll || !state->enableEditing;
    menuState.disableDeSelect = state->selectedRows.empty() || !state->enableEditing;

    menuState.disableMap = state->selectedRows.empty() || !state->enableEditing;
    menuState.disableAddColumn = !state->enableEditing;
}

void DataTableMenu::selectAll() const
{
    state->selectedRows = RowIdxs(state->rows->size());
    std::iota(state->selectedRows.begin(), state->selectedRows.end(), 0);
}

void DataTableMenu::inverseSelect()
{
    inverseSelectIdx = RowIdxs(state->rows->size());
    std::iota(inverseSelectIdx.begin(), inverseSelectIdx.end(), 0);
    std::erase_if(inverseSelectIdx,[&](const int n) {
        return std::ranges::find(state->selectedRows, n) != state->selectedRows.end();
    });
    state->selectedRows = inverseSelectIdx;
}

void DataTableMenu::deselect() const
{
    state->selectedRows.clear();
}

void DataTableMenu::insertRow() const
{
    state->service->reload();
    deselect();
}

void DataTableMenu::deleteRow() const
{
    state->service->deleteRows(state->selectedRows);
    deselect();
}
