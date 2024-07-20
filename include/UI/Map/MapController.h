//
// Created by Aashik on 07-07-2024.
//

#pragma once

#include <UI/UI.h>
#include <State/MapWindowState.h>

#include <memory>

#include <imgui.h>

struct ControllerState
{
    bool leftAltPressed = false, rightAltPressed = false;
    bool leftCtrlPressed = false, rightCtrlPressed = false;
    bool leftMousePressed = false, rightMousePressed = false;
    bool leftMouseReleased = false, rightMouseReleased = false;
    bool leftMouseClicked = false, rightMouseClicked = false;
};

struct MCVec2
{
    double x = 0.0;
    double y = 0.0;
};

class MapController final : public UI
{
public:
    explicit MapController(const std::shared_ptr<MapWindowState>& _state) : state(_state) {}

    void onSetup() override {};
    void onUpdate() override;
    void onKeyEvent() override;

private:

    void mapWheelEvent();
    void mapClickEvent();
    void mapMoveEvent();

    ImVec2 getLocalMousePos();

    MCVec2 lastVelocity;
    ImVec2 lastMousePos;
    bool wasPanning = false;
    float scrollSpanMultiplier = 0.05f;

    std::shared_ptr<MapWindowState> state;
    ControllerState ctrlState;
};
