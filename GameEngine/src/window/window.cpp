#include "window.h"
#include "log/logger.h"
#include <cassert>
#include <glad/glad.h>


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
	// Setup glfw
	glfwInit();
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSwapInterval(0);
	glfwWindowHint(GLFW_SAMPLES, 8);

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
	// Setup glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::log(LOG_ERROR, "Open GL failed to initialze.");
	}
	Logger::log(LOG_SUCCESS, "Open GL initialized successfully.");
	// Setup gl
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Logger::log(LOG_SUCCESS, "Window succesffully initialized.");
}



void GameEngine::Window::pollEvents()
{
	glfwPollEvents();
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