#pragma once
#include <cstdint>
#include <vector>

namespace raytracer
{
	class SurfaceIntegrator;
	class VolumeIntegrator;
	class Scene;

	struct Sample
	{
		// Sample public methods
		Sample(SurfaceIntegrator* surf, VolumeIntegrator* vol, const Scene* scene);
		virtual ~Sample();

		uint32_t add1D(uint32_t num);
		uint32_t add2D(uint32_t num);

		// Camera Sample Data
		double m_imageX, m_imageY;
		double m_lensU, m_lensV;
		double m_time;

		// Integrator Sample Data
		std::vector<uint32_t> m_n1D, m_n2D;
		float** oneD, ** twoD;
	};

	class Sampler
	{
	public:
		// Sampler interface
		Sampler(int xStart, int xEnd, int yStart, int yEnd, int spp);
		virtual bool getNextSample(Sample* sample) = 0;
		virtual int roundSize(int size) const = 0;
		int totalSamples() const;

		// Sampler public data
		int m_xPixelStart, m_xPixelEnd, m_yPixelStart, m_yPixelEnd;
		int m_samplesPerPixel;
	};

}
