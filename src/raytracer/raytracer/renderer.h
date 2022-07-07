#pragma once

#include <ostream>

#include "raytracer/base.h"
#include "utils/glmutils.h"

namespace raytracer
{
	class Image;
	class Hittable;
	class Ray;
	class Camera;

	struct RendererSpecification {
		std::ostream& buffer;
		int samplesPerPixel;
		int recursionDepth;
	};

	class Renderer
	{
	public:
		explicit Renderer(const RendererSpecification& spec);
		void render(Image& image, const ref<Hittable>& world, const ref<Camera>& camera);

	private:
		color rayColor(const Ray& ray, const ref<Hittable>& world, int depth);
		void writeColor(std::ostream& out, color pixelColor, int samplesPerPixel);

	private:
		RendererSpecification m_Specification;
	};

}
