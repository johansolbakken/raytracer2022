#include <iostream>
#include <fstream>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld()
{
	using namespace raytracer;

	ref<HittableList> objects = createRef<HittableList>();

	auto noiseMaterial = createRef<Lambertian>(createRef<NoiseTexture>(4));
	objects->add<Sphere>(point3(0, -1000, 0), 1000, noiseMaterial);
	objects->add<Sphere>(point3(0, 2, 0), 2, noiseMaterial);

	auto difflight = createRef<DiffuseLight>(color(4, 4, 4));
	objects->add<xy_rect>(3, 5, 1, 3, -2, difflight);

	return objects;
}

int main(int argc, char** argv)
{
	std::string filename = "image.ppm";

	if (argc != 1)
	{
		filename = argv[1];
	}

	std::ofstream file(filename, std::ios::out);
	file.clear();

	constexpr auto aspect_ratio = 16.0 / 9.0;

	// Image
	raytracer::Image image{};
	image.aspect_ratio = aspect_ratio;
	image.image_width = 400;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.vfov = 20.0f;
	cameraSpec.aspect_ratio = aspect_ratio;
	cameraSpec.lookFrom = { 26, 3, 6 };
	cameraSpec.lookAt = { 0, 2, 0 };
	cameraSpec.focusDistance = 10.0;
	cameraSpec.aperture = 0.0;
	cameraSpec.time0 = 0.0;
	cameraSpec.time1 = 1.0;

	auto camera = raytracer::createRef<raytracer::Camera>(cameraSpec);

	// render
	raytracer::RendererSpecification rendererSpecification{ .buffer = file };
	rendererSpecification.samplesPerPixel = 32;
	rendererSpecification.recursionDepth = 50;
	rendererSpecification.backgroundColor = { 0.0, 0.0, 0.0 };

	raytracer::Renderer renderer(rendererSpecification);
	renderer.render(image, world, camera);

	file.close();

	return 0;
}
