#include <iostream>
#include <stdio.h>
#include "log/logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window/window.h"


#include "ecs/ecsmanager.h"
#include "ecs/components.h"
#include "ecs/componenttypes.h"
#include <string>
#include "core/application.h"

using std::string;
using std::cout;
using namespace GameEngine;

int main() {
	/*ECSManager ecs{};
	ecs.init();

	Window window{};
	window.init();
	while (!window.shouldClose())
	{
		glfwPollEvents();
		window.clear(0, 0, 0, 1);

		window.swapBuffers();
	}*/
	Application app{};
	app.init();
	app.run();
	


	/*Entity p1 = ecs.addEntity();
	Entity p2 = ecs.addEntity();
	
	ecs.addComponent<Position>(p1, { 0, 0 });
	ecs.addComponent<Size>(p1, { 10, 10 });
	ecs.addComponent<Velocity>(p1, { 1, 1 });
	ecs.addComponent<Acceleration>(p1, { 0.1, 0.1 });
	
	ecs.addComponent<Position>(p2, { 0, 0 });
	ecs.addComponent<Size>(p2, { 10, 10 });
	ecs.addComponent<Velocity>(p2, { 10, 10 });
	ecs.addComponent<Acceleration>(p2, { -0.1, -0.1 });*/

	/*Position p = ecs.getComponent<Position>(p1);
	cout << i << "\n" << p.x << " " << p.y << "\n";

	p = ecs.getComponent<Position>(p2);
	cout << p.x << " " << p.y << "\n\n";*/
	
	return 1;
	
}