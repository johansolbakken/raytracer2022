#include <iostream>
#include <fstream>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld() {
	using namespace raytracer;

	ref<HittableList> objects = createRef<HittableList>();

	auto red   = createRef<Lambertian>(color(.65, .05, .05));
	auto white = createRef<Lambertian>(color(.73, .73, .73));
	auto green = createRef<Lambertian>(color(.12, .45, .15));
	auto light = createRef<DiffuseLight>(color(15, 15, 15));

	objects->add<yz_rect>(0, 555, 0, 555, 555, green);
	objects->add<yz_rect>(0, 555, 0, 555, 0, red);
	objects->add<xz_rect>(213, 343, 227, 332, 554, light);
	objects->add<xz_rect>(0, 555, 0, 555, 0, white);
	objects->add<xz_rect>(0, 555, 0, 555, 555, white);
	objects->add<xy_rect>(0, 555, 0, 555, 555, white);

	return objects;
}

int main(int argc, char** argv)
{
	constexpr auto window_width = 400;
	constexpr auto aspect_ratio = 1.0;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.vfov = 40.0f;
	cameraSpec.aspect_ratio = aspect_ratio;
	cameraSpec.lookFrom = {278, 278, 800};
	cameraSpec.lookAt = {278, 278, 0};
	cameraSpec.focusDistance = 10.0;
	cameraSpec.aperture = 0.0;
	cameraSpec.time0 = 0.0;
	cameraSpec.time1 = 1.0;

	auto camera = raytracer::createRef<raytracer::Camera>(cameraSpec);

	// render
	raytracer::RendererSpecification rendererSpecification;
	rendererSpecification.samplesPerPixel = 32;
	rendererSpecification.recursionDepth = 50;
	rendererSpecification.backgroundColor = { 0, 0, 0};

	raytracer::Renderer renderer(rendererSpecification);
	renderer.onResize(window_width, window_width/aspect_ratio);
	renderer.render( world, camera);

	auto image = renderer.getFinalImage();
	image->flipHorizontal();
	image->save();

	return 0;
}
