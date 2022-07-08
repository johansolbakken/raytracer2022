#include <iostream>
#include <fstream>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld() {
	using namespace raytracer;

	auto material_left = createRef<Lambertian>(color(1, 0, 0));
	auto material_right = createRef<Lambertian>(color(0, 0, 1));

	auto R = std::cos(M_PI/4.0);

	auto world = createRef<HittableList>();
	world->add<Sphere>(point3(-R, 0, -1), R, material_left);
	world->add<Sphere>(point3(R,0, -1), R, material_right);

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
	cameraSpec.vfov = 90.0f;
	cameraSpec.aspect_ratio = image.aspect_ratio;

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
