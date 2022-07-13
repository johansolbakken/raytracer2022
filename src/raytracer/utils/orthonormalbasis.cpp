//
// Created by Johan Solbakken on 7/13/2022.
//

#include "orthonormalbasis.h"

namespace raytracer
{

Vector3 OrthonormalBasis::operator[](int i) const { return axis[i]; }

Vector3 OrthonormalBasis::u() const { return axis[0]; }

Vector3 OrthonormalBasis::v() const { return axis[1]; }

Vector3 OrthonormalBasis::w() const { return axis[2]; }

Vector3 OrthonormalBasis::local(double a, double b, double c) const {
    return a*u() + b*v() + c*w();
}

Vector3 OrthonormalBasis::local(const Vector3 &a) const {
    return a.x*u() + a.y*v() + a.z*w();
}

} // raytracer
