#include <iostream>
#include <fstream>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld() {
	using namespace raytracer;

	auto world = createRef<HittableList>();

	auto texture = createRef<CheckerTexture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
	auto material = createRef<Lambertian>(texture);

	world->add<Sphere>(point3(0,-10,0),10,material);
	world->add<Sphere>(point3(0,10,0),10,material);

	return world;
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
	cameraSpec.lookFrom = {13,2,3};
	cameraSpec.lookAt = {0,0,0};
	cameraSpec.focusDistance = 10.0;
	cameraSpec.aperture = 0.0;
	cameraSpec.time0 = 0.0;
	cameraSpec.time1 = 1.0;

	auto camera = raytracer::createRef<raytracer::Camera>(cameraSpec);

	// render
	raytracer::RendererSpecification rendererSpecification{.buffer = file};
	rendererSpecification.samplesPerPixel = 32;
	rendererSpecification.recursionDepth = 50;
	rendererSpecification.backgroundColor = { 0.70, 0.80, 1.00};

	raytracer::Renderer renderer(rendererSpecification);
	renderer.render(image, world, camera);

	file.close();

	return 0;
}
