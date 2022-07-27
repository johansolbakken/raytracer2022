#pragma once
#include <ostream>

#include "utils/mathutils.h"

namespace raytracer
{
	template <int nSpectrumSamples>
	class CoefficientSpectrum
	{
	public:
		CoefficientSpectrum(double v = 0.f)
		{
			for (int i = 0; i < nSamples; i++)
			{
				c[i] = v;
			}
		}
#ifndef NDEBUG
		CoefficientSpectrum(const CoefficientSpectrum& s) {
			for (int i = 0; i < nSpectrumSamples; ++i)
				c[i] = s.c[i];
		}

		CoefficientSpectrum& operator=(const CoefficientSpectrum& s) {
			for (int i = 0; i < nSpectrumSamples; ++i)
				c[i] = s.c[i];
			return *this;
		}
#endif

		CoefficientSpectrum &operator&=(const CoefficientSpectrum& s2)
		{
			for (int i = 0; i < nSamples; i++)
				c[i] += s2.c[i];
			return *this;
		}

        CoefficientSpectrum operator+(const CoefficientSpectrum& s2) const {
            CoefficientSpectrum ret = *this;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] += s2.c[i];
            return ret;
        }
        CoefficientSpectrum operator-(const CoefficientSpectrum& s2) const {
            CoefficientSpectrum ret = *this;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] -= s2.c[i];
            return ret;
        }
        CoefficientSpectrum operator/(const CoefficientSpectrum& s2) const {
            CoefficientSpectrum ret = *this;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] /= s2.c[i];
            return ret;
        }
        CoefficientSpectrum operator*(const CoefficientSpectrum& sp) const {
            CoefficientSpectrum ret = *this;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] *= sp.c[i];
            return ret;
        }
        CoefficientSpectrum& operator*=(const CoefficientSpectrum& sp) {
            for (int i = 0; i < nSpectrumSamples; ++i)
                c[i] *= sp.c[i];
            return *this;
        }
        CoefficientSpectrum operator*(double a) const {
            CoefficientSpectrum ret = *this;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] *= a;
            return ret;
        }
        CoefficientSpectrum& operator*=(double a) {
            for (int i = 0; i < nSpectrumSamples; ++i)
                c[i] *= a;
            return *this;
        }
        friend inline
            CoefficientSpectrum operator*(double a, const CoefficientSpectrum& s) {
            return s * a;
        }
        CoefficientSpectrum operator/(double a) const {
            CoefficientSpectrum ret = *this;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] /= a;
            Assert(!ret.hasNan());
            return ret;
        }
        CoefficientSpectrum& operator/=(double a) {
            for (int i = 0; i < nSpectrumSamples; ++i)
                c[i] /= a;
            return *this;
        }
        bool operator==(const CoefficientSpectrum& sp) const {
            for (int i = 0; i < nSpectrumSamples; ++i)
                if (c[i] != sp.c[i]) return false;
            return true;
        }
        bool operator!=(const CoefficientSpectrum& sp) const {
            return !(*this == sp);
        }
        bool isBlank() const {
            for (int i = 0; i < nSpectrumSamples; ++i)
                if (c[i] != 0.) return false;
            return true;
        }
        friend CoefficientSpectrum sqrt(const CoefficientSpectrum& s) {
            CoefficientSpectrum ret;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] = std::sqrt(s.c[i]);
            return ret;
        }
        //template <int n> friend CoefficientSpectrum<n> pow(const CoefficientSpectrum<n>& s, double e);
        CoefficientSpectrum operator-() const {
            CoefficientSpectrum ret;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] = -c[i];
            return ret;
        }
        friend CoefficientSpectrum Exp(const CoefficientSpectrum& s) {
            CoefficientSpectrum ret;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] = std::exp(s.c[i]);
            return ret;
        }
        friend std::ostream& operator<<(std::ostream& os, const CoefficientSpectrum& s) {
            os << "[";
            for (int i = 0; i < nSpectrumSamples; ++i) {
                os << s.c[i];
                if (i + 1 < nSpectrumSamples)
                    os << ", ";
            }
            os << "]";
            return os;
        }
        CoefficientSpectrum clamp(double low = 0, double high = math::infinity) const {
            CoefficientSpectrum ret;
            for (int i = 0; i < nSpectrumSamples; ++i)
                ret.c[i] = math::clamp(low, high, c[i]);
            return ret;
        }

		[[nodiscard]] bool hasNan() const {
            for (int i = 0; i < nSpectrumSamples; ++i)
                if (std::isnan(c[i])) return true;
            return false;
        }

        double& operator[](int i) {
            return c[i];
        }
        double operator[](int i) const {
            return c[i];
        }

	public:
		static constexpr int nSamples = nSpectrumSamples;
	protected:
		double c[nSpectrumSamples];
	};
}
