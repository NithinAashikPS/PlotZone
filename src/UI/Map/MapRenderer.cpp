//
// Created by Aashik on 07-07-2024.
//

#include <UI/Map/MapRenderer.h>
#include <imgui.h>

void MapRenderer::onSetup()
{
    initFBO();
    state->map->setupGL();
    state->map->loadScene("file:///C:/Users/Aashik/CLionProjects/PlotZone/res/scene.yaml", false);
}

void MapRenderer::onUpdate()
{
    currentTime = glfwGetTime();
    delta = currentTime - lastTime;
    lastTime = currentTime;

    mapState = state->map->update(static_cast<float>(delta));

    const int width = static_cast<int>(ImGui::GetWindowSize().x);
    const int height = static_cast<int>(ImGui::GetWindowSize().y);

    bindFBO();
    clearFBO();
    resizeFBO(width, height);
    state->map->resize(width, height);
    state->map->render();
    unBindFBO();

    ImGui::Image(reinterpret_cast<ImTextureID>(fbo.texture), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
}

void MapRenderer::initFBO()
{
    glGenFramebuffers(1, &fbo.handler);
    glGenTextures(1, &fbo.texture);
}

void MapRenderer::clearFBO()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void MapRenderer::resizeFBO(const int width, const int height)
{
    if (width != fbo.width || height != fbo.height) {
        fbo.width = width;
        fbo.height = height;

        glBindTexture(GL_TEXTURE_2D, fbo.texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  fbo.width, fbo.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo.texture, 0);
    }
}

void MapRenderer::bindFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo.handler);
}

void MapRenderer::unBindFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
