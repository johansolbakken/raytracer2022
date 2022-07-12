#pragma once

#include "raytracer/renderer.h"
#include "raytracer/image.h"
#include "raytracer/base.h"

#include "hittable/hittable.h"
#include "hittable/hittablelist.h"
#include "shapes/sphere.h"
#include "hittable/movingsphere.h"
#include "hittable/aarect.h"
#include "hittable/box.h"
#include "hittable/constantmedium.h"

#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dielectric.h"
#include "materials/diffuselight.h"
#include "materials/isotropic.h"

#include "cameras/camera.h"

#include "textures/checkertexture.h"
#include "textures/solidcolor.h"
#include "textures/noisetexture.h"
#include "textures/imagetexture.h"