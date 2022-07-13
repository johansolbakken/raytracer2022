#include <iostream>
#include <fstream>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld()
{
	using namespace raytracer;

	auto material_ground = createRef<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center = createRef<Lambertian>(Color(0.1, 0.2, 0.5));
	auto material_left = createRef<Dielectric>(1.5);
	auto material_right = createRef<Metal>(Color(0.8, 0.6, 0.2), 0.0);

	auto world = createRef<HittableList>();
	world->add<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground);
	world->add<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center);
	world->add<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left);
	world->add<Sphere>(Point3(-1.0, 0.0, -1.0), -0.45, material_left);
	world->add<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right);

	return world;
}

int main(int argc, char** argv)
{
	constexpr auto viewport_width = 400;
	constexpr auto aspect_ratio = 16.0 / 9.0;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.vfov = 30.0f;
	cameraSpec.aspect_ratio = aspect_ratio;
	cameraSpec.lookFrom = { -2, 2, 1 };
	cameraSpec.lookAt = { 0, 0.7, 0};

	auto camera = raytracer::createRef<raytracer::Camera>(cameraSpec);

	// render
	raytracer::RendererSpecification rendererSpecification;
	rendererSpecification.samplesPerPixel = 32;
	rendererSpecification.recursionDepth = 50;
	rendererSpecification.backgroundColor = { 0.70, 0.80, 1.00 };

	raytracer::Renderer renderer(rendererSpecification);
    renderer.onResize(viewport_width, uint32_t(viewport_width / aspect_ratio));
	renderer.render(world, camera);

	raytracer::ref<raytracer::Image> image = renderer.getFinalImage();
	image->flipHorizontal();
	image->save();

	return 0;
}
