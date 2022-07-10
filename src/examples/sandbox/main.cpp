#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld()
{
	using namespace raytracer;

	ref<HittableList> objects = createRef<HittableList>();

	auto material = createRef<Lambertian>(Color(1, 0, 0));
	objects->add<Sphere>(Point3(0, 0, 0), 0.5, material);

	return objects;
}

int main(int argc, char** argv)
{
	constexpr auto image_width = 400;
	constexpr auto aspect_ratio = 1.0;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.vfov = 90.0f;
	cameraSpec.aspect_ratio = aspect_ratio;
	cameraSpec.lookFrom = { 0, 0, -2 };
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
	rendererSpecification.backgroundColor = { 0.1, 0.1, 0.1 };

	raytracer::Renderer renderer(rendererSpecification);
	renderer.onResize(image_width, image_width / aspect_ratio);
	renderer.render(world, camera);

	auto image = renderer.getFinalImage();
	image->flipHorizontal();
	image->save();

	return 0;
}
