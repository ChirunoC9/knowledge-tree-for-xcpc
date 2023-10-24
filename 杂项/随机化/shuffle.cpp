#include <algorithm>
#include <random>
#include <vector>

int main() {
    std::vector v{1, 2, 3};

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(v.begin(), v.end(), rng);
}
