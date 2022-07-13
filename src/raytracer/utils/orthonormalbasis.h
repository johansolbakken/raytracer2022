#pragma once
#include "utils/glmutils.h"
namespace raytracer
{

	class OrthonormalBasis
	{
	public:
        OrthonormalBasis() = default;

        Vector3 operator[](int i) const;

        Vector3 u() const;
        Vector3 v() const;
        Vector3 w() const;

        Vector3 local(double a, double b, double c) const;

        Vector3 local(const Vector3& a) const;

        void build_from_w(const Vector3&);

	public:
        Vector3 axis[3];
	};


    inline void OrthonormalBasis::build_from_w(const Vector3& n) {
        axis[2] = glm::normalize(n);
        Vector3 a =  (std::abs(w().x) > 0.9)? Vector3(0,1,0) : Vector3(1,0,0);
        axis[1] = glm::normalize(cross(w(), a));
        axis[0] = glm::cross(w(), v());
	};

} // raytracer
