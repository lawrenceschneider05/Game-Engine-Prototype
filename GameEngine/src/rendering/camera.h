#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "log/logger.h"

namespace GameEngine
{
    class Camera {
    public:
        Camera();
        Camera(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec2& position);

        inline const glm::vec2& GetPosition() const { return position; }

        void SetZoom(float zoom);

        void ZoomOut(float zoom);

        inline void move(glm::vec2 vec)
        {
            Logger::log(LOG_DEBUG, position.x);
            Logger::log(LOG_DEBUG, position.y);
            position += vec;
            Logger::log(LOG_DEBUG, position.x);
            Logger::log(LOG_DEBUG, position.y);
            UpdateView();
        }

        inline float GetZoom() const { return zoom; }

        const glm::vec2 ScreenToWorld(const glm::vec2& screenCoords, const glm::vec2& windowSize);

        void SetViewportSize(float width, float height);

        inline const glm::mat4& GetViewProjectionMatrix() { return viewProjectionMatrix; }

    private:
        void UpdateProjection();

        void UpdateView();

        void UpdateViewProjection();

    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 viewProjectionMatrix;
        glm::vec2 position;
        float zoom;
        glm::vec2 viewportSize;
    };
}
