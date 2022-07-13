#include "flipface.h"


namespace raytracer
{

bool FlipFace::hit(const Ray &r, double t_min, double t_max, hit_record &rec) const {

    if (!ptr->hit(r, t_min, t_max, rec))
        return false;

    rec.front_face = !rec.front_face;
    return true;
}

bool FlipFace::boundingBox(double time0, double time1, Aabb &output_box) const {
    return ptr->boundingBox(time0, time1, output_box);
}

}
