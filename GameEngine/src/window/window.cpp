#include "window.h"
#include "log/logger.h"
#include <cassert>


GameEngine::Window::Window(string title, int width, int height)
{
	this->title = title;
	this->w = width;
	this->h = height;
}


GameEngine::Window::~Window()
{
	glfwDestroyWindow(window);
}

void GameEngine::Window::init()
{
	window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
	if (window == NULL) {
		Logger::log(LOG_ERROR, "GLFW failed to create window context.");
		assert(window);
		return;
	}
	Logger::log(LOG_SUCCESS, "GLFW window context created succesfully");
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height)
	{
			glViewport(0, 0, width, height);
	});
	glfwSwapInterval(1);
}

void GameEngine::Window::onUpdate()
{
	swapBuffers();
}


void GameEngine::Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void GameEngine::Window::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}