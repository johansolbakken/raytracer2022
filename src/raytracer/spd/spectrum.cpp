#include "spectrum.h"

namespace raytracer
{
	SampledSpectrum::SampledSpectrum(double v): CoefficientSpectrum(v)
	{}

	SampledSpectrum::SampledSpectrum(const CoefficientSpectrum<nSpectralSamples>& v)
		: CoefficientSpectrum(v)
	{
	}
}
