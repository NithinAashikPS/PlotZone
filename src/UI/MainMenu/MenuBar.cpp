//
// Created by Aashik on 07-07-2024.
//

#include <UI/MainMenu/MenuBar.h>

void MenuBar::onSetup()
{
    fileMenu->onSetup();
    editMenu->onSetup();
}

void MenuBar::onUpdate()
{
    if (ImGui::BeginViewportSideBar("##SecondaryMenuBar", ImGui::GetMainViewport(), ImGuiDir_Up,
                                    ImGui::GetFrameHeight(),
                                    ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
                                    ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoNav))
    {
        if (ImGui::BeginMenuBar())
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{12.0f, 10.0f});

            if (ImGui::BeginMenu("File"))
            {
                decorateMenu([&]() { fileMenu->onUpdate(); });
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                decorateMenu([&]() { editMenu->onUpdate(); });
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Tools"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Window"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                ImGui::EndMenu();
            }
            ImGui::PopStyleVar();
            ImGui::EndMenuBar();
        }
        ImGui::OpenPopup("Delete?");
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
        ImGui::End();
    }
}

void MenuBar::onKeyEvent()
{
    fileMenu->onKeyEvent();
    editMenu->onKeyEvent();
}

void MenuBar::decorateMenu(const CallBack& callBack) const
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{12.0f, 8.0f});
    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2{-1.0f, 0.0f});
    callBack();
    ImGui::PopStyleVar(2);
}
