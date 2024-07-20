//
// Created by Aashik on 06-07-2024.
//

#pragma once

#include <State/MapWindowState.h>
#include <UI/UI.h>

#include <UI/Map/MapRenderer.h>
#include <UI/Map/MapController.h>

#include <memory>

#include <imgui.h>

using namespace Tangram;

class MapWindow final : public UI
{
public:
    MapWindow() : state(std::make_shared<MapWindowState>()), renderer(std::make_unique<MapRenderer>(state)), controller(std::make_unique<MapController>(state)) {}
    void onSetup() override;
    void onUpdate() override;
    void onKeyEvent() override;

private:

    std::shared_ptr<MapWindowState> state;
    std::unique_ptr<MapRenderer> renderer;
    std::unique_ptr<MapController> controller;
};
