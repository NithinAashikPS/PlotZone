//
// Created by Aashik on 02-07-2024.
//

#include <imgui.h>
#include <imgui_internal.h>
#include <UI/DataTable/DataTableFilter.h>

#include <Utils/Icons.h>

#include "UI/DataTable/DataTableWindow.h"

void DataTableFilter::onSetup()
{
    comboItems.emplace_back("Show All Features");
    comboItems.emplace_back("Show Selected Features");
    currentComboItem = const_cast<char*>(comboItems.at(0).c_str());
}

void DataTableFilter::onUpdate()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 {3.0f, 3.0f});
    ImGui::BeginChild(("TableFilter##" + state->data->id).c_str(), ImVec2 {ImGui::GetWindowSize().x, 30.0f}, ImGuiChildFlags_AlwaysUseWindowPadding);
    ImGui::PopStyleVar();

    currentComboPreviewText = std::string(ICON_MD_FILTER_ALT) + "\t" + currentComboItem + "\t" + std::string(ICON_MD_KEYBOARD_ARROW_DOWN);

    comboBoxWidth = ImGui::CalcTextSize(currentComboPreviewText.c_str()).x + 10.0f;
    ImGui::SetNextItemWidth(comboBoxWidth);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2 {0.0f, 4.0f});
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
    if (ImGui::BeginCombo("##combo", "", ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_CustomPreview)) // The second parameter is the label previewed before opening the combo.
    {
        for (const auto& comboItem: comboItems)
        {
            ImGui::SetCursorPosX(15.0f);
            if (ImGui::Selectable(comboItem.c_str(), false, ImGuiSelectableFlags_SpanAllColumns))
                currentComboItem = const_cast<char*>(comboItem.c_str());
        }
        ImGui::EndCombo();
    }
    ImGui::PopStyleVar(2);

    if (ImGui::BeginComboPreview())
    {
        ImGui::SetCursorPosY(6.0f);
        ImGui::Text(currentComboPreviewText.c_str());
        ImGui::EndComboPreview();
    }

    ImGui::EndChild();
}
