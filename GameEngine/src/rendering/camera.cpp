//#include "camera.h"
//#include "glm/gtc/matrix_transform.hpp"
//#include "log/logger.h"
//#include <string>
//
//using std::to_string;
//
//namespace GameEngine
//{
//	Camera::Camera(vec2 size)
//		: viewportSize(size)
//	{
//		recalculateProjection();
//		recalculateView();
//	}
//
//	void Camera::setPosition(const glm::vec2& position)
//	{
//		this->position = position;
//		recalculateView();
//	}
//
//	void Camera::setZoom(float zoomLevel)
//	{
//		zoom = zoomLevel;
//		recalculateProjection();
//		recalculateView();
//	}
//
//	void Camera::setViewportSize(vec2 size)
//	{
//		viewportSize = size;
//		recalculateProjection();
//	}
//
//	void Camera::zoomOut(float amount)
//	{
//		zoom += amount;
//		Logger::log(LOG_DEBUG, to_string(zoom));
//	}
//
//	void Camera::move(vec2 vector)
//	{
//		position += vector;
//	}
//
//	const mat4& Camera::getViewProjectionMatrix()
//	{
//		recalculateProjection();
//		recalculateView();
//		return viewProjectionMatrix;
//	}
//
//	void Camera::recalculateProjection()
//	{
//		// Update the projection matrix based on the zoom level
//		// The zoom level affects the 'left', 'right', 'top', and 'bottom' values for the orthographic projection
//		float left = -viewportSize.x / 2.0f / zoom;
//		float right = viewportSize.x / 2.0f / zoom;
//		float bottom = -viewportSize.y / 2.0f / zoom;
//		float top = viewportSize.y / 2.0f / zoom;
//
//		// Set up the orthographic projection matrix
//		projectionMatrix = glm::ortho(left, right, bottom, top);
//		recalculateView();
//	}
//
//	void Camera::recalculateView()
//	{
//		/*mat4 transform = translate(glm::mat4(1.0f), vec3(-position, 0.0f));
//		viewMatrix = transform;
//		viewProjectionMatrix = projectionMatrix * viewMatrix;*/
//		viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, 0.0f));
//		viewProjectionMatrix = projectionMatrix * viewMatrix;
//	}
//}
