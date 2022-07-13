
#include <iomanip>
#include <raytracer.h>

using namespace raytracer;

inline double pdf(const glm::vec3& x) {
    return 1.0 / (4.0 * math::pi);
}

int main(){
    int N = 1000000;
    auto sum = 0.0;
    for (int i = 0; i < N; i++) {
        Vector3 d = randomUnitVector();
        auto cosine_squared = d.z * d.z;
        sum += cosine_squared / pdf(d);
    }
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "I=" << sum/double(N) << "\n";
}
