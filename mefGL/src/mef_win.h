#pragma once

#include "core.h"

namespace mef
{
	
	class mef_win
	{
	private:
		GLFWwindow* window;
		int width;
		int height;
	
	public:
		mef_win()
			: width(800), height(600) 	{ }
	
		mef_win(int w, int h)
			: width(w), height(h) { }
	
		~mef_win()
		{
			glfwDestroyWindow(window);
		}

	
		void createWindow(int w, int h, const char* title)
		{
			window = glfwCreateWindow(w, h, title, NULL, NULL);
			if (!window)
			{
				std::cerr << "[MEFGL][ERROR] Failed Creating a Window!\n";
				return;
			}
		}

		void createWindow(const char* title)
		{
			window = glfwCreateWindow(width, height, title, NULL, NULL);
			if (!window)
			{
				std::cerr << "[MEFGL][ERROR] Failed Creating a Window!\n";
				return;
			}
		}
	
		
		void setSize(int w, int h)
		{
			if (!window)
			{
				std::cerr << "[MEFGL][ERROR] Failed setting Window Size!\nYou dont have created a Window!\n";
				return;
			}
	
			width = w;
			height = h;
			glfwSetWindowSize(window, width, height);
		}

		bool stayOpen()
		{
			if (glfwWindowShouldClose(window))
			{
				return false;
			}
			return true;
		}

		void swapBuffers()
		{
			glfwSwapBuffers(window);
		}

		void handleEvents()
		{
			glfwPollEvents();
		}

		void update()
		{

		}

		GLFWwindow* getWin() { return window; }
		int getWidth() { return width; }
		int getHeight() { return height; }
	};

}
