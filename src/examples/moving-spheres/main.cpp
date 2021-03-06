#include <iostream>
#include <fstream>

#include <raytracer.h>

raytracer::ref<raytracer::Hittable> createWorld()
{
	using namespace raytracer;

	auto world = createRef<HittableList>();

	auto ground_material = createRef<Lambertian>(Color(0.5, 0.5, 0.5));
	world->add<Sphere>(Point3(0, -1000, 0), 1000, ground_material);

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto choose_mat = randomdouble();
			Point3 center(a + 0.9 * randomdouble(), 0.2, b + 0.9 * randomdouble());

			if ((center - Point3(4, 0.2, 0)).length() > 0.9)
			{
				ref<Material> sphere_material;

				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo = randomVec3() * randomVec3();
					sphere_material = createRef<Lambertian>(albedo);
					auto center2 = center + Vector3 (0, randomdouble(0, .5), 0);
					world->add<MovingSphere>(center, center2, 0.0, 1.0, 0.2, sphere_material);
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo = randomVec3(0.5, 1);
					auto fuzz = randomdouble(0, 0.5);
					sphere_material = createRef<Metal>(albedo, fuzz);
					world->add<Sphere>(center, 0.2, sphere_material);
				}
				else
				{
					// glass
					sphere_material = createRef<Dielectric>(1.5);
					world->add<Sphere>(center, 0.2, sphere_material);
				}
			}
		}
	}

	auto material1 = createRef<Dielectric>(1.5);
	world->add<Sphere>(Point3(0, 1, 0), 1.0, material1);

	auto material2 = createRef<Lambertian>(Color(0.4, 0.2, 0.1));
	world->add<Sphere>(Point3(-4, 1, 0), 1.0, material2);

	auto material3 = createRef<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world->add<Sphere>(Point3(4, 1, 0), 1.0, material3);

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
	cameraSpec.aperture = 0.1;
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
