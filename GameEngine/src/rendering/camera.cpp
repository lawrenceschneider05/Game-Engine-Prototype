#include "camera.h"

namespace GameEngine
{
	Camera::Camera()
	{
	}
	Camera::Camera(float left, float right, float bottom, float top) : position(0.0f, 0.0f),
		zoom(1.0f), viewportSize(right - left, top - bottom)
	{
		UpdateProjection();
		UpdateView();
	}

	void Camera::SetPosition(const glm::vec2& position)
	{
		this->position = position;
		UpdateView();
	}

	void Camera::SetZoom(float zoom)
	{
		zoom = glm::max(zoom, 0.01f); // Prevent zooming too close
		UpdateProjection();
	}

	void Camera::ZoomOut(float zoom)
	{
		this->zoom += zoom;
		UpdateProjection();
	}

	const glm::vec2 GameEngine::Camera::ScreenToWorld(const glm::vec2& screenCoords, const glm::vec2& windowSize)
	{
		// Convert to NDC (Normalized Device Coordinates)
		// Flip Y-axis because GLFW's origin is top-left
		float ndcX = (2.0f * screenCoords.x) / windowSize.x - 1.0f;
		float ndcY = 1.0f - (2.0f * screenCoords.y) / windowSize.y;

		// Create inverse of view-projection matrix
		glm::mat4 inverseVP = glm::inverse(projectionMatrix * viewMatrix);

		// Transform to world coordinates
		glm::vec4 worldPos = inverseVP * glm::vec4(ndcX, ndcY, 0.0f, 1.0f);

		return glm::vec2(worldPos.x, worldPos.y);
	}

	void Camera::SetViewportSize(float width, float height)
	{
		viewportSize = glm::vec2(width, height);
		UpdateProjection();
	}

	void Camera::UpdateProjection()
	{
		// Calculate zoomed dimensions
		float zoomedWidth = viewportSize.x / zoom;
		float zoomedHeight = viewportSize.y / zoom;

		// Create projection matrix centered at (0,0)
		projectionMatrix = glm::ortho(
			-zoomedWidth / 2, zoomedWidth / 2,
			-zoomedHeight / 2, zoomedHeight / 2,
			-1.0f, 1.0f
		);

		UpdateViewProjection();
	}

	void Camera::UpdateView()
	{
		viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
		UpdateViewProjection();
	}

	void Camera::UpdateViewProjection()
	{
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

}
