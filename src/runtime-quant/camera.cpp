#include "camera.h"

#include "raytracer/ray.h"

namespace qb
{
    Camera::Camera()
    {
        m_position = {0, -10, 0};
        m_lookAt = {0, 0, 0};
        m_up = {0, 1, 0};
        m_length = 1;
        m_horizontalSize = 1;
        m_aspect = 1;
    }

    bool Camera::generateRay(double projScreenX, double projScreenY, raytracer::Ray *cameraRay)
    {
        // projScreenX = u, projScreenY = v

        // Compute the location of the screen in world coordinates
        auto screenWorldCoordinate = m_screenCenter + (m_u * projScreenX) + (m_v * projScreenY);

        if (!cameraRay)
            return false;

        *cameraRay = raytracer::Ray(raytracer::Point3(m_position),
                                    raytracer::Vector3(screenWorldCoordinate - m_position),
                                    0);

        return true;
    }

    void Camera::updateGeometry()
    {
        // Compute vector from the camera position to the lookAt position
        m_alignmentVector = glm::normalize(m_lookAt - m_position);

        // Compute u and v
        m_u = glm::normalize(glm::cross(m_alignmentVector, m_up));
        m_v = glm::normalize(glm::cross(m_u, m_alignmentVector));

        // Compute position of center of the screen
        m_screenCenter = m_position + (m_length * m_alignmentVector);

        // Modify u and v to match the size and aspect ratio
        m_u = m_u * m_horizontalSize;
        m_v = m_v * (m_horizontalSize / m_aspect);
    }
}