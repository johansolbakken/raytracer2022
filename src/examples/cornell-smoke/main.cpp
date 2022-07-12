#include <raytracer.h>
#include "hittable/hittable_transformations.h"

raytracer::ref<raytracer::Hittable> createWorld()
{
	using namespace raytracer;

	auto objects = createRef<HittableList>();

	auto red   = createRef<Lambertian>(Color (.65, .05, .05));
	auto white = createRef<Lambertian>(Color(.73, .73, .73));
	auto green = createRef<Lambertian>(Color(.12, .45, .15));
	auto light = createRef<DiffuseLight>(Color(7, 7, 7));

	objects->add<yz_rect>(0, 555, 0, 555, 555, green);
	objects->add<yz_rect>(0, 555, 0, 555, 0, red);
	objects->add<xz_rect>(113, 443, 127, 432, 554, light);
	objects->add<xz_rect>(0, 555, 0, 555, 555, white);
	objects->add<xz_rect>(0, 555, 0, 555, 0, white);
	objects->add<xy_rect>(0, 555, 0, 555, 555, white);

	ref<Hittable> box1 = createRef<Box>(Point3(0,0,0), Point3 (165,330,165), white);
	box1 = createRef<RotateY>(box1, 15);
	box1 = createRef<Translate>(box1, Vector3 (265,0,295));

	ref<Hittable> box2 = createRef<Box>(Point3(0,0,0), Point3(165,165,165), white);
	box2 = createRef<RotateY>(box2, -18);
	box2 = createRef<Translate>(box2, Vector3(130,0,65));

	objects->add<ConstantMedium>(box1, 0.01, Color(0,0,0));
	objects->add<ConstantMedium>(box2, 0.01, Color(1,1,1));

	return objects;
}

int main(int argc, char** argv)
{
	constexpr auto image_width = 600;
	constexpr auto aspect_ratio = 1.0;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.vfov = 40.0f;
	cameraSpec.aspect_ratio = aspect_ratio;
	cameraSpec.lookFrom = { 278, 278, -800 };
	cameraSpec.lookAt = { 278, 278, 0 };
	cameraSpec.focusDistance = 10.0;
	cameraSpec.aperture = 0.0;
	cameraSpec.time0 = 0.0;
	cameraSpec.time1 = 1.0;

	auto camera = raytracer::createRef<raytracer::Camera>(cameraSpec);

	// render
	raytracer::RendererSpecification rendererSpecification;
	rendererSpecification.samplesPerPixel = 200;
	rendererSpecification.recursionDepth = 50;
	rendererSpecification.backgroundColor = { 0.1, 0.1, 0.1 };

	raytracer::Renderer renderer(rendererSpecification);
	renderer.onResize(image_width, (uint32_t)((double)image_width / aspect_ratio));
	renderer.render(world, camera);

	auto image = renderer.getFinalImage();
	image->flipHorizontal();
	image->save();

	return 0;
}
