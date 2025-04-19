#pragma once
#include <glm/glm.hpp>

using namespace glm;

namespace GameEngine
{
	class Camera
	{
	public:
		Camera() {}
		Camera(vec2 size);

		void setPosition(const vec2& position);
		void setZoom(float zoomLevel);
		void setViewportSize(vec2 size);

		const glm::mat4& getViewProjectionMatrix() const;
	private:
		void recalculateView();
		void recalculateProjection();
	private:
		vec2 position = { 0.0f, 0.0f };
		vec2 viewportSize;
		float zoom = 1.0f;

		mat4 viewMatrix = mat4(1.0f);
		mat4 projectionMatrix = mat4(1.0f);
		mat4 viewProjectionMatrix = mat4(1.0f);
	};
}