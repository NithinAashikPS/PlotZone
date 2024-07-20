//
// Created by Aashik on 06-07-2024.
//

#include <UI/Map/MapWindow.h>

void MapWindow::onSetup()
{
    controller->onSetup();
    renderer->onSetup();
}

void MapWindow::onUpdate()
{
    ImGui::SetNextWindowSize(ImVec2 {700.0f, 450.0f}, ImGuiCond_Appearing);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 {0.0f, 0.0f});
    ImGui::Begin("Map Test Window");
    ImGui::PopStyleVar();

    controller->onKeyEvent();

    renderer->onUpdate();
    controller->onUpdate();

    ImGui::End();
}

void MapWindow::onKeyEvent()
{
}