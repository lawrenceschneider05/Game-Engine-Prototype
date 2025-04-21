#pragma once
#include <glm/glm.hpp>
#include "camera.h"


namespace GameEngine
{
	class Renderer
	{
	public:
		static void init();
		static void shutdown();

		static void beginScene(Camera camera);
		static void endScene();

		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

		static void flush();
		static void setDebugMode(bool);
	private:
	};
}

