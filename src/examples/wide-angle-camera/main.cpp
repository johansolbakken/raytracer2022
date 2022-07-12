#include <iostream>
#include <fstream>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld()
{
	using namespace raytracer;

	auto material_left = createRef<Lambertian>(Color(1, 0, 0));
	auto material_right = createRef<Lambertian>(Color(0, 0, 1));

	auto R = std::cos(M_PI / 4.0);

	auto world = createRef<HittableList>();
	world->add<Sphere>(Point3(-R, 0, -1), R, material_left);
	world->add<Sphere>(Point3(R, 0, -1), R, material_right);

	return world;
}

int main(int argc, char** argv)
{
	constexpr int width = 400;
	constexpr double aspcet_ratio = 16.0/9.0;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.vfov = 90.0f;
	cameraSpec.aspect_ratio = aspcet_ratio;

	auto camera = raytracer::createRef<raytracer::Camera>(cameraSpec);

	// render
	raytracer::RendererSpecification rendererSpecification;
	rendererSpecification.samplesPerPixel = 32;
	rendererSpecification.recursionDepth = 50;
	rendererSpecification.backgroundColor = { 0.70, 0.80, 1.00 };

	raytracer::Renderer renderer(rendererSpecification);
	renderer.onResize(width, int(width * aspcet_ratio));
	renderer.render(world, camera);

	auto image = renderer.getFinalImage();
	image->flipHorizontal();
	image->save();

	return 0;
}
