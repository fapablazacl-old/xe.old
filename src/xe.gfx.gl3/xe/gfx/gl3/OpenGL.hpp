
#pragma once

#ifndef __gl3__
#define __gl3__

#define GLFW_INCLUDE_NONE

#if defined(_MSVC_VER)
#pragma warning (disable:4251)
#endif

#ifdef GL_BINDING
#include <glbinding/Binding.h>
#include <glbinding/gl33core/gl.h>
using namespace gl33core;
#else 
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>

#endif
