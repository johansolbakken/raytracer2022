//
// Created by Johan Solbakken on 7/7/2022.
//

#include "sphere.h"

#include <utility>

#include "raytracer/ray.h"

#include "accelerator/aabb.h"

#include "transformations/transformation.h"

#include "geometry/differentialgeometry.h"

namespace raytracer
{
	Sphere::Sphere(raytracer::Point3 cen, double r, raytracer::ref<raytracer::Material> material)
            :
          #if pbrt
              Shape(nullptr, nullptr, false),
          #endif

              m_center(cen), m_radius(r), m_material(std::move(material))
	{
	}

	bool Sphere::hit(const raytracer::Ray& r, double t_min, double t_max, raytracer::hit_record& rec) const
	{
		Vector3 oc = r.origin() - m_center;
		auto a = lengthSquared(r.direction());
		auto half_b = dot(oc, r.direction());
		auto c = lengthSquared(oc) - m_radius * m_radius;

		auto discriminant = half_b * half_b - a * c;
		if (discriminant < 0) return false;
		auto sqrtd = sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (-half_b - sqrtd) / a;
		if (root < t_min || t_max < root)
		{
			root = (-half_b + sqrtd) / a;
			if (root < t_min || t_max < root)
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		rec.normal = (rec.p - m_center) / m_radius;
		Vector3 outward_normal = (rec.p - m_center) / m_radius;
		rec.setFaceNormal(r, outward_normal);
		rec.mat_ptr = m_material;

		auto[u, v] = getSphereUv(outward_normal);
		rec.u = u;
		rec.v = v;

		return true;
	}


	// Old way to compute bounding box
	bool Sphere::boundingBox(double time0, double time1, Aabb& output_box) const
	{
		output_box = Aabb(
				m_center - Vector3(m_radius, m_radius, m_radius),
				m_center + Vector3(m_radius, m_radius, m_radius)
		);
		return true;
	}

	std::pair<double, double> Sphere::getSphereUv(const Point3& p)
	{
		// p: a given point on the sphere of radius one, centered at the origin.
		// u: returned value [0,1] of angle around the Y axis from X=-1.
		// v: returned value [0,1] of angle from Y=-1 to Y=+1.
		//     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
		//     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
		//     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

		auto theta = std::acos(-p.y);
		auto phi = atan2(-p.z, p.x) + M_PI;

		auto u = phi / (2 * M_PI);
		auto v = theta / M_PI;
		return { u, v };
	}

#if pbrt
	Sphere::Sphere(const ref<Transform>& o2w, const ref<Transform>& w2o, bool ro, double rad, double z0, double z1,
			double pm)
	{

	}

	Sphere::Sphere(const ref<Transform>& o2w, const ref<Transform>& w2o, bool ro, double rad, double z0, double z1,
			double pm) : Shape(o2w, w2o, ro)
	{
		m_radius = rad;
		m_zmin = clamp(std::min(z0, z1), -m_radius, m_radius);
		m_zmax = clamp(std::max(z0, z1), -m_radius, m_radius);
		m_thetaMin = std::acosf(clamp(m_zmin / m_radius, -1.f, 1.f));
		m_thetaMax = std::acosf(clamp(m_zmax / m_radius, -1.f, 1.f));
		m_phiMax = glm::radians(clamp(pm, 0.0f, 360.f));
	}

	Aabb Sphere::objectBound() const
	{
		return { Point3{ -m_radius, -m_radius, m_zmin },
				 { Point3{ m_radius, m_radius, m_zmax }}};
	}

	bool Sphere::intersect(const Ray& r, double* tHit, double* rayEpsilon, ref<DifferentialGeometry>& dg) const
	{
		double phi;
		Point3 phit;

		// Transform ray to object space
		Ray ray = (*worldToObject())(r);

		// Compute quadratic sphere coefficients
		double a = glm::dot(ray.direction(), ray.direction());
		double b = 2.0f * glm::dot(ray.direction(), ray.origin());
		double c = glm::dot(ray.origin(), ray.origin()) - m_radius * m_radius;

		// Solve quadratic equation for t values
		double descriminant = b * b - 4.0f * a * c;
		if (descriminant < 0.0f)
			return false;

		double q;
		if (b < 0) q = -.5f * (b - std::sqrt(descriminant));
		else q = -.5f * (b + std::sqrt(descriminant));

		double t0 = q / a;
		double t1 = c / q;
		if (t0 > t1) std::swap(t0, t1);

		// Compute intersection distance along ray
		if (t0 > ray.maxt() || t1 < ray.mint())
			return false;

		double thit = t0;
		if (t0 < ray.mint())
		{
			thit = t1;

			if (thit > ray.maxt())
				return false;
		}

		// Compare sphere hit position and phi
		phit = ray.at(thit);
		if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * m_radius;
		phi = std::atan2f(phit.y, phit.x);
		if (phi < 0.f) phi += 2.f * M_PI;

		// Test sphere intersection against clipping parameters
		if ((m_zmin > -m_radius && phit.z < m_zmin)
			|| (m_zmax < m_radius && phit.z > m_zmax)
			|| (phi > m_phiMax))
		{
			if (thit == t1) return false;
			if (t1 > ray.maxt()) return false;
			thit = t1;

			// Compute sphere hit position and phi
			phit = ray.at(thit);
			if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * m_radius;
			phi = std::atan2f(phit.y, phit.x);
			if (phi < 0.f) phi += 2.f * M_PI;

			if ((m_zmin > -m_radius && phit.z < m_zmin)
				|| (m_zmax < m_radius && phit.z > m_zmax)
				|| (phi > m_phiMax))
			{
				return false;
			}
		}

		// Find parametric representation of sphere hit
		double u = phi / m_phiMax;
		double theta = std::acosf(clamp(phit.z / m_radius, -1.f, 1.f));
		double v = (theta - m_thetaMin) / (m_thetaMax - m_thetaMin);

		// Compare dpdu and dpdv
		double zradius = std::sqrtf(phit.x * phit.x + phit.y * phit.y);
		double invzradius = 1.f / zradius;
		double cosphi = phit.x * invzradius;
		double sinphi = phit.y * invzradius;
		Vector3 dpdu(-m_phiMax * phit.y, m_phiMax * phit.x, 0);
		Vector3 dpdv =
				(m_thetaMax - m_thetaMin) * Vector3(phit.z * cosphi, phit.z * sinphi, -m_radius * std::sinf(theta));

		// Compare dndu and dndv
		Vector3 d2Pduu = -m_phiMax * m_phiMax * Vector3(phit.x, phit.y, 0);
		Vector3 d2Pduv = (m_thetaMax - m_thetaMin) * phit.z * m_phiMax * Vector3(-sinphi, cosphi, 0.);
		Vector3 d2Pdvv = -(m_thetaMax - m_thetaMin) * (m_thetaMax - m_thetaMin) * Vector3(phit.x, phit.y, phit.z);

		// Compute coefficients for fundemental forms
		double E = glm::dot(dpdu, dpdu);
		double F = glm::dot(dpdu, dpdv);
		double G = glm::dot(dpdv, dpdv);
		Vector3 n = glm::normalize(glm::cross(dpdu, dpdv));
		double e = glm::dot(n, d2Pduu);
		double f = glm::dot(n, d2Pduv);
		double g = glm::dot(n, d2Pdvv);

		// Compute dndu and dndv from fundemental form coefficients
		double invEGF2 = 1.f / (E * G - F * F);
		Vector3 dndu = (f * F - e * G) * invEGF2 * dpdu + (e * F - f * E) * invEGF2 * dpdv;
		Vector3 dndv = (g * F - f * G) * invEGF2 * dpdu + (f * F - g * E) * invEGF2 * dpdv;

		// Initialize DifferentialGeometry from parametric information
		const Transform& o2w = *objectToWorld();
		*dg = DifferentialGeometry(o2w(phit), o2w(dpdu), o2w(dpdv), o2w(dndu), o2w(dndv), u, v, this);

		// Update tHit for quadratic intersection
		*tHit = thit;

		// Compute rayEpsilon for quadratic intersection
		*rayEpsilon = 5e-4f * *tHit;

		return true;
	}

	bool Sphere::intersectP(const Ray& r) const
	{
		double phi;
		Point3 phit;

		// Transform ray to object space
		Ray ray = (*worldToObject())(r);

		// Compute quadratic sphere coefficients
		double a = glm::dot(ray.direction(), ray.direction());
		double b = 2.0f * glm::dot(ray.direction(), ray.origin());
		double c = glm::dot(ray.origin(), ray.origin()) - m_radius * m_radius;

		// Solve quadratic equation for t values
		double descriminant = b * b - 4.0f * a * c;
		if (descriminant < 0.0f)
			return false;

		double q;
		if (b < 0) q = -.5f * (b - std::sqrt(descriminant));
		else q = -.5f * (b + std::sqrt(descriminant));

		double t0 = q / a;
		double t1 = c / q;
		if (t0 > t1) std::swap(t0, t1);

		// Compute intersection distance along ray
		if (t0 > ray.maxt() || t1 < ray.mint())
			return false;

		double thit = t0;
		if (t0 < ray.mint())
		{
			thit = t1;

			if (thit > ray.maxt())
				return false;
		}

		// Compare sphere hit position and phi
		phit = ray.at(thit);
		if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * m_radius;
		phi = std::atan2f(phit.y, phit.x);
		if (phi < 0.f) phi += 2.f * M_PI;

		// Test sphere intersection against clipping parameters
		if ((m_zmin > -m_radius && phit.z < m_zmin)
			|| (m_zmax < m_radius && phit.z > m_zmax)
			|| (phi > m_phiMax))
		{
			if (thit == t1) return false;
			if (t1 > ray.maxt()) return false;
			thit = t1;

			// Compute sphere hit position and phi
			phit = ray.at(thit);
			if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * m_radius;
			phi = std::atan2f(phit.y, phit.x);
			if (phi < 0.f) phi += 2.f * M_PI;

			if ((m_zmin > -m_radius && phit.z < m_zmin)
				|| (m_zmax < m_radius && phit.z > m_zmax)
				|| (phi > m_phiMax))
			{
				return false;
			}
		}

		return true;
	}

	double Sphere::area() const
	{
		return m_phiMax * m_radius * (m_zmax - m_zmin);
	}

	// TODO: Cylinders, disks, quadrics
	// TODO: Triangles and meshes
	// TODO: Implement subdivision surfaces
#endif
}
