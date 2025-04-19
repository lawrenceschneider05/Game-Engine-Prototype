#pragma once
#include <glm/glm.hpp>

using namespace glm;

namespace GameEngine
{
	class Camera
	{
	public:
		mat4 getViewProjMatrix();
	private:
	};
}