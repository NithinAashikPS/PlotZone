#pragma once

#include <functional>
#include <memory>
#include <queue>

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <UI/UI.h>
#include <UI/MainMenu/MenuBar.h>
#include <UI/PopupModal/PopupModal.h>

#include <State/ApplicationState.h>

using Path = std::string;
using Paths = std::vector<Path>;
using onRender = std::function<void()>;
using onDrop = std::function<void(const Paths&)>;

class Application {

public:
    explicit Application(std::string, int _width = 1280, int _height = 720);
    void setOnRenderListener(const onRender&);
    void setOnDropListener(const onDrop&);

    [[nodiscard]] int exec() const;

    void registerUi(std::unique_ptr<UI> ui)
    {
        ui->onSetup();
        uiList.emplace_back(std::move(ui));
    }

    static void exit();

    static ApplicationState state;

private:
    [[nodiscard]] int stop() const;

    std::vector<std::unique_ptr<UI>> uiList;
    std::unique_ptr<PopupModal> popupModal = std::make_unique<PopupModal>();
    std::unique_ptr<MenuBar> menuBar = std::make_unique<MenuBar>();

    static onDrop drop;
    static GLFWwindow* window;
    onRender render;

    int height, width;
    std::string title;
};
