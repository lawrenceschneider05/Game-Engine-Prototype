#pragma once
#include "types.h"
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

using namespace glm;
namespace GameEngine
{
	class Input
	{
	public:
		static void setWindowHandle(GLFWwindow* w);
		static bool isKeyPressed(u16 key);
		static bool isMouseButtonPressed(u16 button);
		static vec2 getMousePosition();

		static f32 getMouseX();
		static f32 getMouseY();
	private:
		static GLFWwindow* window;
	};
}
