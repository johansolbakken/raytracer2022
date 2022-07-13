#pragma once

#include "pdf.h"

#include "utils/orthonormalbasis.h"


namespace raytracer
{

class CosinePdf : public ProbabilityDensityFunction
{
public:
        CosinePdf(const Vector3& w) { uvw.build_from_w(w); }

        virtual double value(const Vector3& direction) const override;

        virtual Vector3 generate() const override;

    public:
        OrthonormalBasis uvw;
};

}
