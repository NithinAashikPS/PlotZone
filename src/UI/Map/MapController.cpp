//
// Created by Aashik on 07-07-2024.
//

#include <iostream>
#include <UI/Map/MapController.h>

#include <util/geom.h>

void MapController::onUpdate()
{
    mapWheelEvent();
    mapClickEvent();
    mapMoveEvent();
}

void MapController::onKeyEvent()
{
    ctrlState.leftAltPressed = ImGui::IsKeyPressed(ImGuiKey_LeftAlt);
    ctrlState.rightAltPressed = ImGui::IsKeyPressed(ImGuiKey_RightAlt);
    ctrlState.leftCtrlPressed = ImGui::IsKeyPressed(ImGuiKey_LeftCtrl);
    ctrlState.rightCtrlPressed = ImGui::IsKeyPressed(ImGuiKey_RightCtrl);
    ctrlState.leftMouseReleased = ImGui::IsMouseReleased(ImGuiPopupFlags_MouseButtonLeft);
    ctrlState.rightMouseReleased = ImGui::IsMouseReleased(ImGuiPopupFlags_MouseButtonRight);
    ctrlState.leftMousePressed = ImGui::IsMouseDown(ImGuiPopupFlags_MouseButtonLeft);
    ctrlState.rightMousePressed = ImGui::IsMouseDown(ImGuiPopupFlags_MouseButtonRight);
}

void MapController::mapMoveEvent()
{
    const ImVec2 currentCursor = getLocalMousePos();
    if (ctrlState.leftMousePressed) {

        if (wasPanning) {
            state->map->handlePanGesture(lastMousePos.x, lastMousePos.y, currentCursor.x, currentCursor.y);
        }
        wasPanning = true;
        lastMousePos = currentCursor;
    }
}

void MapController::mapClickEvent()
{
    const ImVec2 currentCursor = getLocalMousePos();

    if (wasPanning && ctrlState.leftMouseReleased) {
        wasPanning = false;
        const auto vx = static_cast<float>(clamp(lastVelocity.x, -2000.0, 2000.0));
        const auto vy = static_cast<float>(clamp(lastVelocity.y, -2000.0, 2000.0));
        state->map->handleFlingGesture(currentCursor.x, currentCursor.y, vx, vy);
    }
}

void MapController::mapWheelEvent()
{
    if (ImGui::IsItemHovered())
    {
        const ImVec2 currentCursor = getLocalMousePos();

        if (ctrlState.leftCtrlPressed || ctrlState.rightCtrlPressed) {
            state->map->handleShoveGesture(scrollSpanMultiplier * ImGui::GetIO().MouseWheel);
        } else if (ctrlState.leftAltPressed || ctrlState.rightAltPressed) {
            state->map->handleRotateGesture(currentCursor.x, currentCursor.y, scrollSpanMultiplier * ImGui::GetIO().MouseWheel);
        } else {
            state->map->handlePinchGesture(currentCursor.x, currentCursor.y, 1.0f + scrollSpanMultiplier * ImGui::GetIO().MouseWheel, 0.0f);
        }
    }
}

ImVec2 MapController::getLocalMousePos()
{
    const ImVec2 mousePos = ImGui::GetIO().MousePos;
    return ImVec2 {mousePos.x - ImGui::GetWindowPos().x, mousePos.y - ImGui::GetWindowPos().y - ImGui::GetFrameHeight()};
}
