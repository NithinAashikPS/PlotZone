//
// Created by Aashik on 07-07-2024.
//

#pragma once

#include <UI/UI.h>

class EditMenu final : public UI
{
public:
    void onUpdate() override;
    void onSetup() override;
    void onKeyEvent() override;
};
