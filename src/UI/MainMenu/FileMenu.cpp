//
// Created by Aashik on 07-07-2024.
//

#include <UI/MainMenu/FileMenu.h>

#include <Application.h>

void FileMenu::onSetup()
{

}

void FileMenu::onUpdate()
{
    if (ImGui::BeginMenu("New" EMPTY_SPACE4))
    {
        if (ImGui::MenuItemEx("Table window", ICON_MD_TABLE_VIEW)) { Application::state.newTableWindowModal = true; }
        if (ImGui::MenuItemEx("Map window", ICON_MD_MAP)) { Application::state.newMapWindowModal = true; }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItemEx("Open..." EMPTY_SPACE4, ICON_MD_FOLDER, "Ctrl+O"))
    {
    }
    ImGui::Separator();
    if (ImGui::MenuItemEx("Settings..." EMPTY_SPACE4, ICON_MD_SETTINGS, "Ctrl+Alt+S"))
    {
    }
    ImGui::Separator();
    if (ImGui::BeginMenu("Export" EMPTY_SPACE4))
    {
        ImGui::EndMenu();
    }
    if (ImGui::MenuItemEx("Print" EMPTY_SPACE4, ICON_MD_PRINT))
    {
    }
    ImGui::Separator();
    if (ImGui::MenuItem("Exit" EMPTY_SPACE4)) { Application::exit(); }
    newPopupModel();
}

void FileMenu::onKeyEvent()
{

}

void FileMenu::newPopupModel()
{
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Delete?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!");
        ImGui::Separator();

        static bool dont_ask_me_next_time = false;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
        ImGui::PopStyleVar();

        if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}
