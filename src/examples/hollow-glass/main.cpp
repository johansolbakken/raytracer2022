#include <iostream>
#include <fstream>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld() {
	using namespace raytracer;

	auto material_ground = createRef<Lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = createRef<Lambertian>(color(0.1, 0.2, 0.5));
	auto material_left   = createRef<Dielectric>(1.5);
	auto material_right  = createRef<Metal>(color(0.8, 0.6, 0.2));

	auto world = createRef<HittableList>();
	world->add<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground);
	world->add<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center);
	world->add<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left);
	world->add<Sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left);
	world->add<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right);

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

	// Image
	raytracer::Image image{};
	image.aspect_ratio = 16.0 / 9.0;
	image.image_width = 400;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.aspect_ratio = image.aspect_ratio;
	cameraSpec.vfov = 90.0f;

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
