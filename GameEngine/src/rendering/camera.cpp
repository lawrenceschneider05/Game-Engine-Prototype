#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"


namespace GameEngine
{
	Camera::Camera(vec2 size)
		: viewportSize(size)
	{
		recalculateProjection();
		recalculateView();
	}

	void Camera::setPosition(const glm::vec2& position)
	{
		this->position = position;
		recalculateView();
	}

	void Camera::setZoom(float zoomLevel)
	{
		zoom = zoomLevel;
		recalculateProjection();
		recalculateView();
	}

	void Camera::setViewportSize(vec2 size)
	{
		viewportSize = size;
		recalculateProjection();
	}

	const mat4& Camera::getViewProjectionMatrix() const
	{
		return viewProjectionMatrix;
	}

	void Camera::recalculateProjection()
	{
		float halfWidth = (viewportSize.x * 0.5f) / zoom;
		float halfHeight = (viewportSize.y * 0.5f) / zoom;
		projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void Camera::recalculateView()
	{
		mat4 transform = translate(glm::mat4(1.0f), vec3(-position, 0.0f));
		viewMatrix = transform;
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}
