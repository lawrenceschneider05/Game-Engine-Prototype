#pragma once
#include "window/window.h"
#include "types.h"
#include "rendering/camera.h"
#include "game.h"

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

		Game* game;

		void update(f64 dt);
		void render(f64 dt);
		const u32 screenWidth = 1600;
		const u32 screenHeight = 900;
		i32 x = 0, y = x;
	};
}