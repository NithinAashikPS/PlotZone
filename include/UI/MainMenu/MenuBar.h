//
// Created by Aashik on 07-07-2024.
//

#pragma once

#include <UI/UI.h>
#include <UI/MainMenu/FileMenu.h>
#include <UI/MainMenu/EditMenu.h>

#include <memory>
#include <functional>

using CallBack = std::function<void()>;

class MenuBar final : public UI
{
public:
    void onSetup() override;
    void onUpdate() override;
    void onKeyEvent() override;

private:
    void decorateMenu(const CallBack&) const;

    std::unique_ptr<FileMenu> fileMenu = std::make_unique<FileMenu>();
    std::unique_ptr<EditMenu> editMenu = std::make_unique<EditMenu>();
};
