//
// Created by Aashik on 03-07-2024.
//

#include <imgui_internal.h>
#include <UI/DataTable/DataTableWindow.h>

void DataTableWindow::onSetup()
{
    dataTableMenu->onSetup();
    dataTableQuery->onSetup();
    dataTable->onSetup();
    dataTableFilter->onSetup();
}

void DataTableWindow::onUpdate()
{
    ImGui::SetNextWindowSize(ImVec2 {600.0f, 400.0f}, ImGuiCond_Appearing);

    // if (!data->isReady)
    //     sprintf(loadingBuffer, "Loading %c %s###%s", "|/-\\"[(int)(ImGui::GetTime() / 0.25f) & 3], data->input.name.c_str(), data->id.c_str());
    // else
    // sprintf(loadingBuffer, "%s###%s", data->input.name.c_str(), data->id.c_str());

    // ImGui::Begin(loadingBuffer, nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 {0.0f, 0.0f});
    ImGui::Begin( ("Table [" + state->data->input.name + "]##" + state->data->id).c_str(), &enableClose, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
    ImGui::PopStyleVar();

    dataTableMenu->onUpdate();
    if (state->enableEditing)
    { //ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
        dataTableQuery->onUpdate();
    }
    dataTable->onUpdate();
    dataTableFilter->onUpdate();

    ImGui::End();
}

void DataTableWindow::onKeyEvent()
{
    dataTableMenu->onKeyEvent();
    if (state->enableEditing)
        dataTableQuery->onKeyEvent();
    dataTable->onKeyEvent();
    dataTableFilter->onKeyEvent();
}
