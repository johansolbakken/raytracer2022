#pragma once

#include "utils/glmutils.h"
namespace raytracer
{

class ProbabilityDensityFunction
{
public:
    virtual ~ProbabilityDensityFunction() = default;

    virtual double value(const Vector3 &direction) const = 0;
    virtual Vector3 generate() const = 0;
};

}
