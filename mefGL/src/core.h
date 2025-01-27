#pragma once

#include <glad/glad.h>
#include "GLFW\glfw3.h"
#include <iostream>

namespace mef
{
	enum class Profile
	{
		Core = GLFW_OPENGL_CORE_PROFILE, Any = GLFW_OPENGL_ANY_PROFILE, Compat = GLFW_OPENGL_COMPAT_PROFILE
	};

	enum class DRAW_MODE
	{
		STATIC = GL_STATIC_DRAW, DYNAMIC=GL_DYNAMIC_DRAW
	};

	enum class MEF_ENUM
	{
		MEF_FLOAT = GL_FLOAT, MEF_FALSE = GL_FALSE, MEF_TRUE = GL_TRUE, MEF_UNSIGNED_INT = GL_UNSIGNED_INT, MEF_UNSIGNED_BYTE = GL_UNSIGNED_BYTE
	};

	enum class SYNC
	{
		UNLIMITED = 0, ON = 1
	};

	int initMef()
	{
		if (!glfwInit())
		{
			std::cerr << "[MEFGL][ERROR] Failed Initializing GLFW!\n";
			return -1;
		}


	}

	int initOpenGL(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "[MEFGL][ERROR] Failed to initialize GLAD\n";
			return -1;
		}
	}

	void setOpenGLProfile(uint32_t major, uint32_t minor, Profile profile)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, (uint32_t)profile);
	}

	void clearColorBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void clearDepthBuffer()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void setVsync(mef::SYNC par)
	{
		glfwSwapInterval((int)par);
	}
	
}
