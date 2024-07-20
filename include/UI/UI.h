//
// Created by Aashik on 22-06-2024.
//

#pragma once

#include <imgui.h>
#include <imgui_internal.h>

#include <Utils/Icons.h>

class UI
{
public:
    virtual ~UI() = default;

    virtual void onSetup() = 0;
    virtual void onUpdate() = 0;
    virtual void onKeyEvent() {};
};
