#pragma once
#include <unordered_map>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "window/window.h"

#define KEY_A 1
#define KEY_B 2
#define KEY_C 3
#define KEY_D 4
#define KEY_E 5
#define KEY_F 6
#define KEY_G 7
#define KEY_H 8
#define KEY_I 9
#define KEY_J 10
#define KEY_K 11
#define KEY_L 12
#define KEY_M 13
#define KEY_N 14
#define KEY_O 15
#define KEY_P 16
#define KEY_Q 17
#define KEY_R 18
#define KEY_S 19
#define KEY_T 20
#define KEY_U 21
#define KEY_V 22
#define KEY_W 23
#define KEY_X 24
#define KEY_Y 25
#define KEY_Z 26
#define KEY_ESCAPE 27
#define KEY_LEFT_CTRL 28
#define KEY_RIGHT_CTRL 29
#define KEY_LEFT_SHIFT 30
#define KEY_RIGHT_SHIFT 31
#define KEY_LEFT_ALT 32
#define KEY_RIGHT_ALT 33
#define KEY_1 34
#define KEY_2 35
#define KEY_3 36
#define KEY_4 37
#define KEY_5 38
#define KEY_6 39
#define KEY_7 40
#define KEY_8 41
#define KEY_9 42
#define KEY_0 43
#define KEY_ENTER 44
#define KEY_SPACE 45
#define KEY_UP 46
#define KEY_DOWN 47
#define KEY_LEFT 48
#define KEY_RIGHT 49

namespace GameEngine
{
	class InputManager
	{
	public:
		InputManager(Window* window);
		~InputManager();

		void keyPressed(int glfwKey);
		void keyReleased(int glfwKey);
		bool keyDown(int key);

		inline glm::vec2 getMousePos()
		{
			return { mousePos.x, window->getWindowSize().y - mousePos.y };
		}

		inline void mouseMoved(double x, double y)
		{
			mousePos.x = x;
			mousePos.y = y;
		}

		inline bool isLeftMousePressed()
		{
			return leftMouseDown;
		}

		inline void leftMousePressed()
		{
			leftMouseDown = true;
		}
		inline void leftMouseReleased()
		{
			leftMouseDown = false;
		}

		inline bool isRightMousePressed()
		{
			return rightMouseDown;
		}

		inline void rightMousePressed()
		{
			rightMouseDown = true;
		}
		inline void rightMouseReleased()
		{
			rightMouseDown = false;
		}

	private:
		Window* window;
		bool keysDown[44] = {};

		double mousePosX = 0, mousePosY = 0;

		bool leftMouseDown = false;
		bool rightMouseDown = false;

		glm::vec2 mousePos = { 0,0 };

		std::unordered_map<int, int> keyMap = { {GLFW_KEY_A, KEY_A},
												{GLFW_KEY_B, KEY_B},
												{GLFW_KEY_C, KEY_C},
												{GLFW_KEY_D, KEY_D},
												{GLFW_KEY_E, KEY_E},
												{GLFW_KEY_F, KEY_F},
												{GLFW_KEY_G, KEY_G},
												{GLFW_KEY_H, KEY_H},
												{GLFW_KEY_I, KEY_I},
												{GLFW_KEY_J, KEY_J},
												{GLFW_KEY_K, KEY_K},
												{GLFW_KEY_L, KEY_L},
												{GLFW_KEY_M, KEY_M},
												{GLFW_KEY_N, KEY_N},
												{GLFW_KEY_O, KEY_O},
												{GLFW_KEY_P, KEY_P},
												{GLFW_KEY_Q, KEY_Q},
												{GLFW_KEY_R, KEY_R},
												{GLFW_KEY_S, KEY_S},
												{GLFW_KEY_T, KEY_T},
												{GLFW_KEY_U, KEY_U},
												{GLFW_KEY_V, KEY_V},
												{GLFW_KEY_W, KEY_W},
												{GLFW_KEY_X, KEY_X},
												{GLFW_KEY_Y, KEY_Y},
												{GLFW_KEY_Z, KEY_Z},
												{GLFW_KEY_ESCAPE, KEY_ESCAPE},
												{GLFW_KEY_LEFT_CONTROL, KEY_LEFT_CTRL},
												{GLFW_KEY_RIGHT_CONTROL, KEY_RIGHT_CTRL},
												{GLFW_KEY_LEFT_SHIFT, KEY_LEFT_SHIFT},
												{GLFW_KEY_RIGHT_SHIFT, KEY_RIGHT_SHIFT},
												{GLFW_KEY_LEFT_ALT, KEY_LEFT_ALT},
												{GLFW_KEY_RIGHT_ALT, KEY_RIGHT_ALT},
												{GLFW_KEY_1, KEY_1},
												{GLFW_KEY_2, KEY_2},
												{GLFW_KEY_3, KEY_3},
												{GLFW_KEY_4, KEY_4},
												{GLFW_KEY_5, KEY_5},
												{GLFW_KEY_6, KEY_6},
												{GLFW_KEY_7, KEY_7},
												{GLFW_KEY_8, KEY_8},
												{GLFW_KEY_9, KEY_9},
												{GLFW_KEY_0, KEY_0},
												{GLFW_KEY_ENTER, KEY_ENTER},
												{GLFW_KEY_SPACE, KEY_SPACE},
												{GLFW_KEY_UP, KEY_UP},
												{GLFW_KEY_DOWN, KEY_DOWN},
												{GLFW_KEY_LEFT, KEY_LEFT},
												{GLFW_KEY_RIGHT, KEY_RIGHT},
		};
	};
}