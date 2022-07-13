#include "cosinepdf.h"

namespace raytracer
{

double CosinePdf::value(const Vector3 &direction) const {
    auto cosine = glm::dot(glm::normalize(direction), uvw.w());
    return (cosine <= 0) ? 0 : cosine/math::pi;
}

Vector3 CosinePdf::generate() const {
    return uvw.local(randomCosineDirection());
}

}
