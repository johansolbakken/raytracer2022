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
		SolidColor() = default;

		explicit SolidColor(color c);

		SolidColor(double red, double green, double blue);

		[[nodiscard]] color value(double u, double v, const vec3& p) const override;

	private:
		color m_colorValue{};
	};

} // raytracer

#endif //RAY_SOLIDCOLOR_H
