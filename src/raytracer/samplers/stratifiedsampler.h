#pragma once

#include "sampler.h"

namespace raytracer
{

	class StratifiedSampler: public Sampler
	{
	public:
		// Public methods
		StratifiedSampler(int x0, int x1, int y0, int y1, int xs, int ys, bool jitter);

		int roundSize(int size) const override;
		bool getNextSample(Sample* sample) override;

		void stratifiedSample1D(float* samp, int nSamples, bool jitter) const;
		void stratifiedSample2D(float* samp, int nx, int ny, bool jitter) const;
		void shuffle(float* samp, int coun, int dim) const;

	private:
		// Private data
		int m_xPixelSamples, m_yPixelSamples;
		bool m_jitterSamples;
		int m_xPos, m_yPos;

		float* m_imageSamples, * m_lensSamples, * m_timeSamples;

		int m_samplePos;
	};

}
