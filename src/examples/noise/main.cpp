#include <iostream>
#include <fstream>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld()
{
	using namespace raytracer;

	auto world = createRef<HittableList>();

	auto pertex = createRef<NoiseTexture>(4);
	auto material = createRef<Lambertian>(pertex);

	world->add<Sphere>(Point3(0, -1000, 0), 1000, material);
	world->add<Sphere>(Point3(0, 2, 0), 2, material);

	return world;
}

int main(int argc, char** argv)
{
	constexpr int width = 400;
	constexpr double aspect_ratio = 16.0/9.0;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.vfov = 20.0f;
	cameraSpec.aspect_ratio = aspect_ratio;
	cameraSpec.lookFrom = { 13, 2, 3 };
	cameraSpec.lookAt = { 0, 0, 0 };
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
	renderer.onResize(width, int(width * aspect_ratio));
	renderer.render(world, camera);

	auto image = renderer.getFinalImage();
	image->flipHorizontal();
	image->save();


	return 0;
}
