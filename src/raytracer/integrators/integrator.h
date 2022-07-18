#pragma once

namespace raytracer
{
	class Sample;
	class Scene;

	class SurfaceIntegrator
	{
	public:
		void requestSamples(Sample* sample, const Scene* scene);
	};

	class VolumeIntegrator
	{
	public:
		void requestSamples(Sample* sample, const Scene* scene);
	};
}
