#include <iostream>
#include <fstream>
#include <filesystem>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld() {
	using namespace raytracer;

	std::cout << "Please enter filepath for image: ";
	std::string filepath;
	std::cin >> filepath;

	if (!std::filesystem::exists(filepath)) {
		std::cout << "Not a valid path!, exiting..." << std::endl;
		exit(-1);
	}

	auto earth_texture = createRef<ImageTexture>(filepath);
	auto earth_surface = createRef<Lambertian>(earth_texture);
	auto globe = createRef<Sphere>(point3(0,0,0), 2, earth_surface);

	return createRef<HittableList>(globe);
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
