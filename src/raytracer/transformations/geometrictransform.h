#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
    class Ray;

    enum class TransformFlag
    {
        Forward,
        Backward
    };

    class GeometricTransform
    {
    public:
        GeometricTransform();
        ~GeometricTransform();
        explicit GeometricTransform(const Matrix4 &forward, const Matrix4 &backward);

        void setTransform(const Vector3 &translation,
                          const Vector3 &rotation,
                          const Vector3 &scale);
        Matrix4 forwardMatrix() const;
        Matrix4 backwardMatrix() const;

        Ray apply(const Ray &inputRay, TransformFlag dirFlag);

        friend GeometricTransform operator*(const GeometricTransform &lhs, const GeometricTransform &rhs);
        GeometricTransform operator=(const GeometricTransform &rhs);

        Vector3 apply(const Vector3 &vector, TransformFlag dirFlag);

        void printMatrix(bool dirFlag);

    private:
        Matrix4 m_forwardMatrix;
        Matrix4 m_backardMatrix;
    };
}