//
// Created by Aashik on 07-07-2024.
//

#pragma once

#include <UI/UI.h>

class FileMenu final : public UI
{
public:
    void onSetup() override;
    void onUpdate() override;
    void onKeyEvent() override;

private:
    void newPopupModel();
};
