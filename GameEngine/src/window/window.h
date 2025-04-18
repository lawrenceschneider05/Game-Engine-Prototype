#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include "glm/glm.hpp"

using std::string;

namespace GameEngine
{
	class Window
	{
	private:
		void swapBuffers();
		
	public:
		Window(string title = "Game Engine", int width = 1600, int height = 900);
		~Window();
		void init();
		void onUpdate();
		bool shouldClose() { return glfwWindowShouldClose(window); }
		void clear(float r, float g, float b, float a);

		inline glm::vec2 getWindowSize() {
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			glm::vec2 vec = { width, height };
			return vec;
		}
	private:
		GLFWwindow* window;
		int w,h;
		string title;
	};
}