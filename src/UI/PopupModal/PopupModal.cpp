//
// Created by Aashik on 07-07-2024.
//

#include <UI/PopupModal/PopupModal.h>

#include <Application.h>

void PopupModal::onSetup()
{

}

void PopupModal::onUpdate()
{
    prepareModals();
    if (Application::state.newTableWindowModal)
    {
        Application::state.newTableWindowModal = false;
        ImGui::OpenPopup("TableWindowModal");
        return;
    }
    if (Application::state.newMapWindowModal)
    {
        Application::state.newMapWindowModal = false;
        ImGui::OpenPopup("MapWindowModal");
        return;
    }
}

void PopupModal::onKeyEvent()
{

}

void PopupModal::prepareModals()
{

}
