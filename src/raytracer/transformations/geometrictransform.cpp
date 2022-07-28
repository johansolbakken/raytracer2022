#include "geometrictransform.h"

#include "raytracer/ray.h"

#include <iostream>

namespace raytracer
{
    GeometricTransform::GeometricTransform()
    {
        m_forwardMatrix = Matrix4(1.0);
        m_backardMatrix = Matrix4(1.0);
    }

    GeometricTransform::~GeometricTransform()
    {
    }

    GeometricTransform::GeometricTransform(const Matrix4 &forward, const Matrix4 &backward)
    {
        m_forwardMatrix = forward;
        m_backardMatrix = backward;
    }

    void GeometricTransform::setTransform(const Vector3 &translation,
                                          const Vector3 &rotation,
                                          const Vector3 &scale)
    {
        // Computing matrices
        Matrix4 translationMatrix = glm::translate(Matrix4(1.0), translation);
        Matrix4 rotationMatrixX = glm::rotate(Matrix4(1.0), rotation.x, {1, 0, 0});
        Matrix4 rotationMatrixY = glm::rotate(Matrix4(1.0), rotation.y, {0, 1, 0});
        Matrix4 rotationMatrixZ = glm::rotate(Matrix4(1.0), rotation.z, {0, 0, 1});
        Matrix4 scaleMatrix = glm::scale(Matrix4(1.0), scale);

        // Computing forward matrix
        m_forwardMatrix = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ;
        m_backardMatrix = glm::inverse(m_forwardMatrix);
    }

    Matrix4 GeometricTransform::getForward()
    {
        return m_forwardMatrix;
    }
    Matrix4 GeometricTransform::getBackward()
    {
        return m_backardMatrix;
    }

    Ray GeometricTransform::apply(const Ray &inputRay, bool dirFlag)
    {
        Ray ray;
        Point3 endPoint = inputRay.origin() + inputRay.direction();

        if (dirFlag)
        {
            // Apply forward transform
            ray.setOrigin(this->apply(inputRay.origin(), TransformFlag::Forward));
            endPoint = this->apply(endPoint, TransformFlag::Forward);
        }
        else
        {
            // Apply backward transform
            ray.setOrigin(this->apply(inputRay.origin(), TransformFlag::Backward));
            endPoint = this->apply(endPoint, TransformFlag::Backward);
        }

        // Point ray to new endpoint
        ray.setDirection(endPoint - ray.origin());
        return ray;
    }

    Vector3 GeometricTransform::apply(const Vector3 &vector, TransformFlag dirFlag)
    {
        Vector4 tempVector(vector, 1.0);

        Vector4 resultVector;
        if (dirFlag == TransformFlag::Forward)
        {
            resultVector = m_forwardMatrix * tempVector;
        }
        else if (dirFlag == TransformFlag::Backward)
        {
            resultVector = m_backardMatrix * tempVector;
        }

        return {resultVector.x, resultVector.y, resultVector.z};
    }

    GeometricTransform operator*(const GeometricTransform &lhs, const GeometricTransform &rhs)
    {
        auto fwdResult = lhs.m_forwardMatrix * rhs.m_forwardMatrix;
        auto bckResult = glm::inverse(fwdResult);
        return {fwdResult, bckResult};
    }

    GeometricTransform GeometricTransform::operator=(const GeometricTransform &rhs)
    {
        if (this != &rhs)
        {
            m_forwardMatrix = rhs.m_forwardMatrix;
            m_backardMatrix = rhs.m_backardMatrix;
        }
        
        return *this;
    }

    void GeometricTransform::printMatrix(bool dirFlag)
    {
        std::cout << "Print Matrix in GeometricTransform not implemented!" << std::endl;
    }
}