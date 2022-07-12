//
// Created by Johan Solbakken on 7/8/2022.
//

#ifndef RAY_SOLIDCOLOR_H
#define RAY_SOLIDCOLOR_H

#include "texture.h"

namespace raytracer
{

	class SolidColor : public Texture
	{
	public:
		SolidColor() = default;

		explicit SolidColor(Color c);

		SolidColor(double red, double green, double blue);

		[[nodiscard]] Color value(double u, double v, const Vector3& p) const override;

	private:
		Color m_colorValue{};
	};

} // raytracer

#endif //RAY_SOLIDCOLOR_H
