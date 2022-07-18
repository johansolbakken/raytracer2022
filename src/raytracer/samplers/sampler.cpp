#include "samplers/sampler.h"

#include "integrators/integrator.h"
#include "scene/scene.h"

namespace raytracer
{
	Sample::Sample(SurfaceIntegrator* surf, VolumeIntegrator* vol, const Scene* scene)
	{
		surf->requestSamples(this, scene);
		vol->requestSamples(this, scene);

		// allocate storage for sample pointers
		int nPtrs = m_n1D.size() + m_n2D.size();
		if (!nPtrs)
		{
			oneD = twoD = nullptr;
			return;
		}

		oneD = (float**)new float*[nPtrs * sizeof(float*)];
		twoD = oneD + m_n1D.size();

		// Compute total number of sample values needed
		int totSamples = 0;
		for (const uint32_t i : m_n1D)
			totSamples += i;
		for (const uint32_t i : m_n2D)
			totSamples += 2 * i;

		// Allocate storage for sample values
		float* mem = (float*)new float[totSamples * sizeof(float)];
		for (uint32_t i = 0; i < m_n1D.size(); i++)
		{
			oneD[i] = mem;
			mem += m_n1D[i];
		}

		for (uint32_t i = 0; i < m_n2D.size(); i++)
		{
			twoD[i] = mem;
			mem += 2 * m_n2D[i];
		}
	}

	Sample::~Sample()
	{
		int nPtrs = m_n1D.size() + m_n2D.size();
		if (!nPtrs)
		{
			oneD = twoD = nullptr;
			return;
		}

		for (int i = 0; i < nPtrs; i++)
		{
			delete[] oneD[i];
		}

		delete[] oneD;
	}

	uint32_t Sample::add1D(uint32_t num)
	{
		m_n1D.push_back(num);
		return m_n1D.size() - 1;
	}

	uint32_t Sample::add2D(uint32_t num)
	{
		m_n2D.push_back(num);
		return m_n2D.size() - 1;
	}

	Sampler::Sampler(int xStart, int xEnd, int yStart, int yEnd, int spp)
		: m_xPixelStart(xStart), m_xPixelEnd(xEnd), m_yPixelStart(yStart), m_yPixelEnd(yEnd), m_samplesPerPixel(spp)
	{
	}

	int Sampler::totalSamples() const
	{
		return m_samplesPerPixel * (m_yPixelEnd - m_yPixelStart) * (m_xPixelEnd - m_xPixelStart);
	}
}
