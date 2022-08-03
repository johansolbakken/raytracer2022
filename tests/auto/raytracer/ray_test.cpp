#include <gtest/gtest.h>

#include <raytracer/ray.h>

TEST(RayTest, testAt)
{
    raytracer::Ray ray;
    ray.setDirection({1, 1, 1});
    ray.setOrigin({0, 0, 0});

    auto expected = raytracer::Point3(1, 1, 1);
    auto actual = ray.at(1);

    EXPECT_EQ(expected.x, actual.x);
    EXPECT_EQ(expected.y, actual.y);
    EXPECT_EQ(expected.z, actual.z);
}