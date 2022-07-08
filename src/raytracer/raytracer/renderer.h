#pragma once

#include <ostream>

#include "raytracer/base.h"
#include "utils/glmutils.h"
#include "image.h"
#include "cameras/camera.h"

namespace raytracer
{
	class Image;
	class Hittable;
	class Ray;
	class Camera;

	struct RendererSpecification {
		int samplesPerPixel;
		int recursionDepth;
		color backgroundColor={0,0,0};

	};

	class Renderer
	{
	public:
		explicit Renderer(const RendererSpecification& spec);
		void render(const ref<Hittable>& world, const ref<Camera>& camera);
		void onResize(uint32_t width, uint32_t height);
		uint32_t perPixel(glm::vec2 coord);

		raytracer::ref<raytracer::Image> getFinalImage();

	private:
		color rayColor(const Ray& ray, const ref<Hittable>& world, int depth);

	private:
		RendererSpecification m_Specification;

		uint32_t m_viewportWidth;
		uint32_t m_viewportHeight;

		ref<Image> m_finalImage;
		uint32_t* m_imageData = nullptr;

		ref<Camera> m_camera;
		ref<Hittable> m_world;
	};

}
