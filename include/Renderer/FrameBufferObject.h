//
// Created by Aashik on 07-07-2024.
//

#pragma once

#include <glad/glad.h>

struct FrameBufferObject
{
    int width = 0, height = 0;
    GLuint handler = 0, texture = 0;
};
