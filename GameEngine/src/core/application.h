#pragma once
#include "window/window.h"
#include "types.h"
#include "rendering/camera.h"

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
		Camera camera;

		void update(f64 dt);
		void render();
	};
}