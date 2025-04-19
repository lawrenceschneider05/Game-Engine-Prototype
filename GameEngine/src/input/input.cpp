#include "input.h"

namespace GameEngine
{
	GLFWwindow* Input::window = nullptr;

	void Input::setWindowHandle(GLFWwindow* w)
	{
		window = w;
	}
	bool Input::isKeyPressed(u16 key)
	{
		return (glfwGetKey(window, key) == GLFW_PRESS);
	}
	bool Input::isMouseButtonPressed(u16 button)
	{
		return (glfwGetMouseButton(window, button) == GLFW_PRESS);
	}
	vec2 Input::getMousePosition()
	{
		if (!window) { return { 0,0 }; }
		f64 xpos = 0, ypos = 0;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { xpos, ypos };
	}
	f32 Input::getMouseX()
	{
		return getMousePosition().x;
	}
	f32 Input::getMouseY()
	{
		return getMousePosition().y;
	}
}