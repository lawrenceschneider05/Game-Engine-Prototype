#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace GameEngine
{
    class Camera {
    public:
        Camera() {}
        Camera(float left, float right, float bottom, float top)
            : m_Position(0.0f, 0.0f),
            m_Zoom(1.0f),
            m_ViewportSize(right - left, top - bottom)
        {
            UpdateProjection();
            UpdateView();
        }

        // Set camera position (center point)
        void SetPosition(const glm::vec2& position) {
            m_Position = position;
            UpdateView();
        }

        // Get camera position
        const glm::vec2& GetPosition() const { return m_Position; }

        // Set zoom level (1.0 = normal, >1.0 = zoom in, <1.0 = zoom out)
        void SetZoom(float zoom) {
            m_Zoom = glm::max(zoom, 0.01f); // Prevent zooming too close
            UpdateProjection();
        }
        void ZoomOut(float zoom)
        {
            m_Zoom += zoom;
            UpdateProjection();
        }
        // Get current zoom level
        float GetZoom() const { return m_Zoom; }

        // Convert screen coordinates to world coordinates
        glm::vec2 ScreenToWorld(const glm::vec2& screenCoords, const glm::vec2& windowSize) const {
            // Convert to NDC (Normalized Device Coordinates)
            // Flip Y-axis because GLFW's origin is top-left
            float ndcX = (2.0f * screenCoords.x) / windowSize.x - 1.0f;
            float ndcY = 1.0f - (2.0f * screenCoords.y) / windowSize.y;

            // Create inverse of view-projection matrix
            glm::mat4 inverseVP = glm::inverse(m_ProjectionMatrix * m_ViewMatrix);

            // Transform to world coordinates
            glm::vec4 worldPos = inverseVP * glm::vec4(ndcX, ndcY, 0.0f, 1.0f);

            return glm::vec2(worldPos.x, worldPos.y);
        }

        // Handle window resize
        void SetViewportSize(float width, float height) {
            m_ViewportSize = glm::vec2(width, height);
            UpdateProjection();
        }

        // Get the view-projection matrix for rendering
        const glm::mat4& GetViewProjectionMatrix() const {
            return m_ViewProjectionMatrix;
        }

    private:
        void UpdateProjection() {
            // Calculate zoomed dimensions
            float zoomedWidth = m_ViewportSize.x / m_Zoom;
            float zoomedHeight = m_ViewportSize.y / m_Zoom;

            // Create projection matrix centered at (0,0)
            m_ProjectionMatrix = glm::ortho(
                -zoomedWidth / 2, zoomedWidth / 2,
                -zoomedHeight / 2, zoomedHeight / 2,
                -1.0f, 1.0f
            );

            UpdateViewProjection();
        }

        void UpdateView() {
            // View matrix is just a translation based on camera position
            m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-m_Position, 0.0f));
            UpdateViewProjection();
        }

        void UpdateViewProjection() {
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        glm::vec2 m_Position;
        float m_Zoom;
        glm::vec2 m_ViewportSize;
    };
}
