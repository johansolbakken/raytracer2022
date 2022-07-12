#include <raytracer.h>
#include "hittable/hittable_transformations.h"
#include "hittable/bvh.h"

raytracer::ref<raytracer::Hittable> createWorld()
{
	using namespace raytracer;

	HittableList boxes1;
	auto ground = createRef<Lambertian>(Color(0.48, 0.83, 0.53));

	const int boxes_per_side = 20;
	for (int i = 0; i < boxes_per_side; i++)
	{
		for (int j = 0; j < boxes_per_side; j++)
		{
			auto w = 100.0;
			auto x0 = -1000.0 + i * w;
			auto z0 = -1000.0 + j * w;
			auto y0 = 0.0;
			auto x1 = x0 + w;
			auto y1 = randomdouble(1, 101);
			auto z1 = z0 + w;

			boxes1.add<Box>(Point3(x0, y0, z0), Point3(x1, y1, z1), ground);
		}
	}

	auto objects = createRef<HittableList>();

	objects->add<BvhNode>(boxes1, 0, 1);

	auto light = createRef<DiffuseLight>(Color(7, 7, 7));
	objects->add<xz_rect>(123, 423, 147, 412, 554, light);

	auto center1 = Point3(400, 400, 200);
	auto center2 = center1 + Vector3(30, 0, 0);
	auto moving_sphere_material = createRef<Lambertian>(Color(0.7, 0.3, 0.1));
	objects->add<MovingSphere>(center1, center2, 0, 1, 50, moving_sphere_material);

	objects->add<Sphere>(Point3(260, 150, 45), 50, createRef<Dielectric>(1.5));
	objects->add<Sphere>(Point3(0, 150, 145), 50, createRef<Metal>(Color(0.8, 0.8, 0.9), 1.0));

	auto boundary = createRef<Sphere>(Point3(360, 150, 145), 70, createRef<Dielectric>(1.5));
	objects->add(boundary);
	objects->add<ConstantMedium>(boundary, 0.2, Color(0.2, 0.4, 0.9));
	boundary = createRef<Sphere>(Point3(0, 0, 0), 5000, createRef<Dielectric>(1.5));
	objects->add<ConstantMedium>(boundary, .0001, Color(1, 1, 1));

	auto emat = createRef<Lambertian>(createRef<ImageTexture>(R"(C:\Dev\Ray\src\examples\earth-image\images\earthmap.jpg)"));
	objects->add<Sphere>(Point3(400, 200, 400), 100, emat);
	auto pertext = createRef<NoiseTexture>(0.1);
	objects->add<Sphere>(Point3(220, 280, 300), 80, createRef<Lambertian>(pertext));

	HittableList boxes2;
	auto white = createRef<Lambertian>(Color(.73, .73, .73));
	int ns = 1000;
	for (int j = 0; j < ns; j++)
	{
		boxes2.add<Sphere>(randomVec3(0, 165), 10, white);
	}

	objects->add<Translate>(createRef<RotateY>(createRef<BvhNode>(boxes2, 0.0, 1.0), 15), Vector3(-100, 270, 395));

	return objects;
}

int main(int argc, char** argv)
{
	constexpr auto image_width = 800;
	constexpr auto aspect_ratio = 1.0;

	// World
	auto world = createWorld();

	// Camera
	raytracer::CameraSpecification cameraSpec;
	cameraSpec.vfov = 40.0f;
	cameraSpec.aspect_ratio = aspect_ratio;
	cameraSpec.lookFrom = { 478, 278, -600 };
	cameraSpec.lookAt = { 278, 278, 0 };
	cameraSpec.focusDistance = 10.0;
	cameraSpec.aperture = 0.0;
	cameraSpec.time0 = 0.0;
	cameraSpec.time1 = 1.0;

	auto camera = raytracer::createRef<raytracer::Camera>(cameraSpec);

	// render
	raytracer::RendererSpecification rendererSpecification;
	rendererSpecification.samplesPerPixel = 32;
	rendererSpecification.recursionDepth = 50;
	rendererSpecification.backgroundColor = { 0,0,0 };

	raytracer::Renderer renderer(rendererSpecification);
	renderer.onResize(image_width, (uint32_t)((double)image_width / aspect_ratio));
	renderer.render(world, camera);

	auto image = renderer.getFinalImage();
	image->flipHorizontal();
	image->save();

	return 0;
}
