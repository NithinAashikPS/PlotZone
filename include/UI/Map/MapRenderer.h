//
// Created by Aashik on 07-07-2024.
//

#pragma once

#include <UI/UI.h>
#include <State/MapWindowState.h>
#include <Renderer/FrameBufferObject.h>

#include <GLFW/glfw3.h>

class MapRenderer final : public UI
{
public:
    explicit MapRenderer(const std::shared_ptr<MapWindowState>& _state) : state(_state) {}

    void onSetup() override;
    void onUpdate() override;

private:
    void initFBO();
    void bindFBO();
    void clearFBO();
    void unBindFBO();
    void resizeFBO(int, int);
    FrameBufferObject fbo;

    double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    double delta = 0;
    MapState mapState;

    std::shared_ptr<MapWindowState> state;
};
