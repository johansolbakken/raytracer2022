#include <iostream>
#include <fstream>
#include <filesystem>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld()
{
	using namespace raytracer;

	std::cout << "Please enter filepath for image: ";
	std::string filepath;
	std::cin >> filepath;

	if (!std::filesystem::exists(filepath))
	{
		std::cout << "Not a valid path!, exiting..." << std::endl;
		exit(-1);
	}

	auto earth_texture = createRef<ImageTexture>(filepath);
	auto earth_surface = createRef<Lambertian>(earth_texture);
	auto globe = createRef<Sphere>(Point3(0, 0, 0), 2, earth_surface);

	return createRef<HittableList>(globe);
}

int main(int argc, char** argv)
{
	constexpr auto image_width = 400;
	constexpr auto aspect_ratio = 16.0 / 9.0;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.vfov = 20.0f;
	cameraSpec.aspect_ratio = aspect_ratio;
	cameraSpec.lookFrom = { 13, 2, 3 };
	cameraSpec.lookAt = { 1, 2, -3 };
	cameraSpec.focusDistance = 10.0;
	cameraSpec.aperture = 0.0;
	cameraSpec.time0 = 0.0;
	cameraSpec.time1 = 1.0;

	auto camera = raytracer::createRef<raytracer::Camera>(cameraSpec);

	// render
	raytracer::RendererSpecification rendererSpecification;
	rendererSpecification.samplesPerPixel = 32;
	rendererSpecification.recursionDepth = 50;
	rendererSpecification.backgroundColor = { 0.70, 0.80, 1.00 };

	raytracer::Renderer renderer(rendererSpecification);
	renderer.onResize(image_width, image_width / aspect_ratio);
	renderer.render(world, camera);

	auto image = renderer.getFinalImage();
	image->flipHorizontal();
	image->save();

	return 0;
}
