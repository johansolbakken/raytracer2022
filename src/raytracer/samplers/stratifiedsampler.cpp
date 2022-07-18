#include "samplers/stratifiedsampler.h"

#include "utils/mathutils.h"

namespace raytracer
{
	StratifiedSampler::StratifiedSampler(int x0, int x1, int y0, int y1, int xs, int ys, bool jitter)
		: Sampler(x0, x1, y0, y1, xs * ys), m_jitterSamples(jitter)
	{
		m_xPos = x0;
		m_yPos = y0;
		m_xPixelSamples = xs;
		m_yPixelSamples = ys;

		// Allocate storage for a pixels worth of stratified samples
		m_imageSamples = new float[5 * m_xPixelSamples * m_yPixelSamples * sizeof(float)];
		m_lensSamples = m_imageSamples + 2 * m_xPixelSamples * m_yPixelSamples;
		m_timeSamples = m_lensSamples + 2 * m_xPixelSamples * m_yPixelSamples;

		// Generate stratified camera samples for (xPos,yPos)
		stratifiedSample2D(m_imageSamples, m_xPixelSamples, m_yPixelSamples, m_jitterSamples);
		stratifiedSample2D(m_lensSamples, m_xPixelSamples, m_yPixelSamples, m_jitterSamples);
		stratifiedSample1D(m_timeSamples, m_xPixelSamples * m_yPixelSamples, m_jitterSamples);

		// Shift stratified image to pixel coordinates
		for (int o = 0; o < 2 * m_xPixelSamples * m_yPixelSamples; o += 2) {
			m_imageSamples[o] += m_xPos;
			m_imageSamples[o + 1] += m_yPos;
		}

		// Decorrelate sample dimensions
		shuffle(m_lensSamples, m_xPixelSamples * m_yPixelSamples, 2);
		shuffle(m_timeSamples, m_xPixelSamples * m_yPixelSamples, 1);

		m_samplePos = 0;

	}

	int StratifiedSampler::roundSize(int size) const
	{
		return size;
	}

	bool StratifiedSampler::getNextSample(Sample* sample)
	{
		// Compute new set of samples if needed for next pixel
		if (m_samplePos == m_xPixelSamples * m_yPixelSamples)
		{
			// Advance to next pixel for stratified sampling
			if (++m_xPos == m_xPixelEnd)
			{
				m_xPos = m_xPixelStart;
				++m_yPos;
			}
			if (m_yPos == m_yPixelEnd)
				return false;

			// Generate stratified camera samples for (xPos, yPos)
			stratifiedSample2D(m_imageSamples, m_xPixelSamples, m_yPixelSamples, m_jitterSamples);
			stratifiedSample2D(m_lensSamples, m_xPixelSamples, m_yPixelSamples, m_jitterSamples);
			stratifiedSample1D(m_timeSamples, m_xPixelSamples * m_yPixelSamples, m_jitterSamples);

			// Shift stratified image to pixel coordinates
			for (int o = 0; o < 2 * m_xPixelSamples * m_yPixelSamples; o += 2) {
				m_imageSamples[o] += m_xPos;
				m_imageSamples[o + 1] += m_yPos;
			}

			// Decorrelate sample dimensions
			shuffle(m_lensSamples, m_xPixelSamples * m_yPixelSamples, 2);
			shuffle(m_timeSamples, m_xPixelSamples * m_yPixelSamples, 1);

			m_samplePos = 0;
		}

		// Return stratifiedSampler sample point
		sample->m_imageX = m_imageSamples[2 * m_samplePos];
		sample->m_imageY = m_imageSamples[2 * m_samplePos + 1];

		return true;
	}

	void StratifiedSampler::stratifiedSample1D(float* samp, const int nSamples, const bool jitter) const
	{
		const float invTot = 1.f / nSamples;
		for (int i = 0; i < nSamples; i++)
		{
			float j = jitter ? randomdouble() : 0.5f;
			*samp++ = (i + j) * invTot;
		}
	}

	void StratifiedSampler::stratifiedSample2D(float* samp, const int nx, const int ny, const bool jitter) const
	{
		const float dx = 1.f / nx;
		const float dy = 1.f / ny;
		for(int y = 0; y < ny; y++)
		{
			for (int x = 0; x < nx; x++)
			{
				const float jx = jitter ? randomdouble() : 0.5;
				const float jy = jitter ? randomdouble() : 0.5;
				*samp++ = (x + jx) * dx;
				*samp++ = (y + jy) * dy;
			}
		}
	}

	void StratifiedSampler::shuffle(float* samp, const int count, const int dim) const
	{
		for (int i = 0; i < count; i++)
		{
			const auto other = static_cast<uint32_t>(randomdouble());
			for (int j = 0; j < dim; j++)
			{
				std::swap(samp[dim * i + j], samp[dim * other + j]);
			}
		}
	}
}
