#include "InputManager.h"
#include <iostream>
namespace GameEngine
{
	InputManager::InputManager(Window* w)
	{
		window = w;
	}

	InputManager::~InputManager()
	{

	}

	bool InputManager::keyDown(int key)
	{
		return keysDown[key];
	}

	void InputManager::keyPressed(int glfwKey)
	{
		keysDown[keyMap[glfwKey]] = true;
	}

	void InputManager::keyReleased(int glfwKey)
	{
		keysDown[keyMap[glfwKey]] = false;
	}
}