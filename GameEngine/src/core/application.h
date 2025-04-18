#pragma once
#include "window/window.h"
#include "types.h"

namespace GameEngine
{
	class Application
	{
	public:
		Application();
		~Application();
		void init();
		void run();
	private:
		Window window;
		void update(f64 dt) {}
		void render() {}
	};
}