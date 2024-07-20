//
// Created by Aashik on 07-07-2024.
//

#pragma once

#include <Renderer/Renderer.h>

#include <memory>

#include <map.h>

using namespace Tangram;
class MapWindowState
{
public:
    MapWindowState() : platform(std::make_unique<Renderer>()), map(std::make_unique<Map>(std::move(platform))) {}
    std::unique_ptr<Platform> platform;
    std::unique_ptr<Map> map;
};
