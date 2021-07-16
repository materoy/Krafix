
#pragma once
#ifndef glad_h
#include <glad/glad.h>
#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

