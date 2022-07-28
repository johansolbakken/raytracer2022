#pragma once

#include "vec.h"

namespace raytracer
{
    class Ray;
}

namespace qb
{

    class Camera
    {
    public:
        Camera();

        void setPosition(const Point3 &pos) { m_position = pos; }
        void setLookAt(const Point3 &pos) { m_lookAt = pos; }
        void setUp(const Vector3 &up) { m_up = up; }
        void setLength(double length) { m_length = length; }
        void setHorizontalSize(double size) { m_horizontalSize = size; }
        void setAspect(double aspect) { m_aspect = aspect; }

        Point3 position() const { return m_position; }
        Point3 lookAt() const { return m_lookAt; }
        Vector3 up() const { return m_up; }
        Vector3 u() const { return m_u; }
        Vector3 v() const { return m_v; }
        double length() const { return m_length; }
        double horizontalSize() const { m_horizontalSize; }
        double aspect() const { return m_aspect; }
        Point3 screenCenter() const { return m_screenCenter; }

        bool generateRay(double projScreenX, double projScreenY, raytracer::Ray* cameraRay);

        void updateGeometry();

    private:
        Point3 m_position;
        Point3 m_lookAt;
        Vector3 m_up;
        double m_length;
        double m_horizontalSize;
        double m_aspect;

        Vector3 m_alignmentVector;
        Vector3 m_u;
        Vector3 m_v;
        Vector3 m_screenCenter;
    };

}