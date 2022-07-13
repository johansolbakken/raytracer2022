#pragma once

#include "hittable.h"

namespace raytracer
{

class FlipFace : public Hittable {
public:
        FlipFace(ref<Hittable> p) : ptr(p) {}

        virtual bool hit(
            const Ray& r, double t_min, double t_max, hit_record& rec) const override;

        virtual bool boundingBox(double time0, double time1, Aabb& output_box) const override;

    public:
        ref<Hittable> ptr;
};

}
