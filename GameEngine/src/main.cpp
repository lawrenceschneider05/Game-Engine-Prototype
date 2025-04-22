#include "core/application.h"

using namespace GameEngine;

int main() {
	Application app{};
	app.init();
	app.run();
	return 1;
	
}