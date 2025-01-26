#pragma once

#include "GLFW\glfw3.h"
#include <iostream>

namespace mef
{
	enum class Profile
	{
		Core = GLFW_OPENGL_CORE_PROFILE, Any = GLFW_OPENGL_ANY_PROFILE, Compat = GLFW_OPENGL_COMPAT_PROFILE
	};

	int initMef()
	{
		if (!glfwInit())
		{
			std::cerr << "[MEFGL][ERROR] Failed Initializing GLFW!\n";
			return -1;
		}
	}

	void setOpenGLProfile(uint32_t major, uint32_t minor, Profile profile)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, (uint32_t)profile);
	}
}
