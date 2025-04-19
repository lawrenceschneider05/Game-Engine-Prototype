#pragma once
#include <glm/glm.hpp>
#include "vertexarray.h"
#include <memory>

using std::shared_ptr;

namespace GameEngine
{
	class RenderCommand
	{
	public:
		static void init();
		static void setClearColor(const glm::vec4& color);
		static void clear();
		static void drawIndexed(const shared_ptr<VertexArray>& va);
	};
}