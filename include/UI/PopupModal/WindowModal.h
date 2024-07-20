//
// Created by Aashik on 08-07-2024.
//

#pragma once

#include <functional>
#include <string>

#include <../../../cmake-build-debug/vcpkg_installed/x64-mingw-dynamic/include/imgui.h>


using RenderBody = std::function<bool()>;

class WindowModal
{
public:
    void renderWindow(const std::pmr::string& windowName, const RenderBody& renderBody)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
        if (ImGui::BeginPopupModal(windowName.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
        {
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 15.0f));
            ImGui::SetNextItemWidth(330.0f);
            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 0, 0, 0));
            ImGui::SetKeyboardFocusHere();
            closeWindow = renderBody();
            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar();

            ImGui::SetCursorPosY(120.0f - ImGui::GetFrameHeight() + 5.0f);
            ImGui::SetWindowFontScale(0.8f);
            ImGui::BeginDisabled(true);
            ImGui::Text("Press 'Esc' key to close this window.");
            ImGui::EndDisabled();
            ImGui::SetWindowFontScale(1.0f);
            if (closeWindow)
            {
                closeWindow = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::PopStyleVar();
    }

    bool closeWindow = false;
};
