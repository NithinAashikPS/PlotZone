//
// Created by Aashik on 07-07-2024.
//

#include <UI/MainMenu/EditMenu.h>

void EditMenu::onSetup()
{
}

void EditMenu::onUpdate()
{
    if (ImGui::MenuItemEx("Undo" EMPTY_SPACE4, ICON_MD_UNDO, "Ctrl+Z"))
    {
        /* Undo action */
    }
    if (ImGui::MenuItemEx("Redo" EMPTY_SPACE4, ICON_MD_REDO, "Ctrl+Y"))
    {
        /* Redo action */
    }
    ImGui::Separator();
    if (ImGui::MenuItemEx("Cut" EMPTY_SPACE4, ICON_MD_CONTENT_CUT, "Ctrl+X"))
    {
        /* Undo action */
    }
    if (ImGui::MenuItemEx("Copy" EMPTY_SPACE4, ICON_MD_CONTENT_COPY, "Ctrl+C"))
    {
        /* Redo action */
    }
    if (ImGui::BeginMenu("Paste" EMPTY_SPACE4))
    {
        if (ImGui::MenuItemEx("Paste" EMPTY_SPACE4, ICON_MD_CONTENT_PASTE, "Ctrl+V"))
        {
            /* Undo action */
        }
        if (ImGui::MenuItem("Paste from History" EMPTY_SPACE4, "Ctrl+Shift+V"))
        {
            /* Redo action */
        }
        if (ImGui::MenuItem("Paste as Plain Text" EMPTY_SPACE4, "Ctrl+Alt+Shift+V"))
        {
            /* Redo action */
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Delete" EMPTY_SPACE4, "Del"))
    {
        /* Redo action */
    }

}

void EditMenu::onKeyEvent()
{
}
