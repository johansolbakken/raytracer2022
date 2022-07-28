#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
    class Ray;

    class GeometricTransform
    {
    public:
        GeometricTransform();
        ~GeometricTransform();
        GeometricTransform(const Matrix4 &forward, const Matrix4 &backward);

        void setTransform(const Vector3 &translation,
                                            const Vector3 &rotation,
                                            const Vector3 &scale);
        Matrix4 getForward();
        Matrix4 getBackward();

        Ray apply(const Ray &inputRay, bool dirFlag);

    private:
        enum class TransformFlag {
            Forward, Backward
        };

        Vector3 apply(const Vector3 &vector, TransformFlag dirFlag);

        friend GeometricTransform operator*(const GeometricTransform &lhs, const GeometricTransform &rhs);
        GeometricTransform operator=(const GeometricTransform &rhs);

        void printMatrix(bool dirFlag);

    private:
        Matrix4 m_forwardMatrix;
        Matrix4 m_backardMatrix;
    };
}