#pragma once

#include "coefficientspectrum.h"

namespace raytracer
{
	static constexpr int sampledLambdaStart = 400;
	static constexpr int sampledLambdaEnd = 700;
	static constexpr int nSpectralSamples = 60;

	class SampledSpectrum : public CoefficientSpectrum<nSpectralSamples>
	{
	public:
		SampledSpectrum(double v = 0.f);
		explicit SampledSpectrum(const CoefficientSpectrum<nSpectralSamples>& v);

	private:
		static SampledSpectrum X, Y, Z;
		static SampledSpectrum rgbRefl2SpectWhite, rgbRefl2SpectCyan;
		static SampledSpectrum rgbRefl2SpectMagenta, rgbRefl2SpectYellow;
		static SampledSpectrum rgbRefl2SpectRed, rgbRefl2SpectGreen;
		static SampledSpectrum rgbRefl2SpectBlue;
		static SampledSpectrum rgbIllum2SpectWhite, rgbIllum2SpectCyan;
		static SampledSpectrum rgbIllum2SpectMagenta, rgbIllum2SpectYellow;
		static SampledSpectrum rgbIllum2SpectRed, rgbIllum2SpectGreen;
		static SampledSpectrum rgbIllum2SpectBlue;
	};

	class RGBSpectrum {};

	using Spectrum = RGBSpectrum;

}