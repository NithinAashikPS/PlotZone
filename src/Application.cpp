#include "Application.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <iostream>

#include <utility>

#include <Utils/Icons.h>

ApplicationState Application::state;
onDrop Application::drop = nullptr;
GLFWwindow* Application::window = nullptr;

Application::Application(std::string _title, const int _width, const int _height) : height(_height), width(_width),
    title(std::move(_title))
{
    if (glfwInit())
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window != nullptr)
        {
            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);

#ifdef TANGRAM_WINDOWS
            gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
#endif

            glfwSetDropCallback(window, [](GLFWwindow*, const int count, const char** paths)
            {
                if (drop)
                    drop(Paths(paths, paths + count));
            });

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            (void)io;

            ImFontConfig font_cfg;
            font_cfg.OversampleH = 3;
            font_cfg.OversampleV = 3;
            io.Fonts->AddFontFromFileTTF("C:/Users/Aashik/CLionProjects/ImGuiTest/font/LatoRegular.ttf", 16.0f,
                                         &font_cfg);

            static const ImWchar icon_ranges[] = {ICON_MIN_MD, ICON_MAX_16_MD, 0};
            ImFontConfig icon_config;
            icon_config.MergeMode = true;
            icon_config.PixelSnapH = true;
            icon_config.OversampleH = 3;
            icon_config.OversampleV = 3;
            icon_config.GlyphOffset = ImVec2{0.0f, 2.0f};
            icon_config.GlyphMinAdvanceX = 16.0f;
            io.Fonts->AddFontFromFileTTF("C:/Users/Aashik/CLionProjects/ImGuiTest/font/MaterialIcons-Regular.ttf",
                                         16.0f, &icon_config, icon_ranges);

            ImGui::StyleColorsDark();
            // ImGui::StyleColorsLight();

            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowRounding = 6.0f;
            style.WindowBorderSize = 0.0f;
            style.WindowTitleAlign = ImVec2{0.5f, 0.5f};

            style.ChildRounding = 3.0f;
            style.ChildBorderSize = 0.0f;

            style.ItemSpacing = ImVec2{0.0f, 3.0f};

            style.PopupRounding = 3.0f;
            style.PopupBorderSize = 0.0f;

            style.FramePadding = ImVec2{6.0f, 6.0f};
            style.FrameRounding = 3.0f;
            style.FrameBorderSize = 0.0f;

            style.ScrollbarSize = 10.0f;
            // style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
            // style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 130");
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            popupModal->onSetup();
            menuBar->onSetup();
        }
    }
}

void Application::setOnDropListener(const onDrop& _onDrop)
{
    drop = _onDrop;
}

void Application::setOnRenderListener(const onRender& _onRender)
{
    render = _onRender;
}

int Application::exec() const
{
    if (window == nullptr)
        return 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), 0);

        popupModal->onKeyEvent();
        popupModal->onUpdate();
        menuBar->onKeyEvent();
        menuBar->onUpdate();

        if (ImGui::BeginViewportSideBar("##MainStatusBar", ImGui::GetMainViewport(), ImGuiDir_Down,
                                        ImGui::GetFrameHeight(),
                                        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
                                        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoNav))
        {
            if (ImGui::BeginMenuBar())
            {
                ImGui::Text("Happy status bar");
                ImGui::EndMenuBar();
            }
            ImGui::End();
        }

        if (render != nullptr)
            render();

        for (const auto& ui : uiList)
        {
            ui->onKeyEvent();
            ui->onUpdate();
        }
        // ImGui::PopFont();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    return stop();
}

int Application::stop() const
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}

void Application::exit()
{
    glfwSetWindowShouldClose(window, 1);
}
