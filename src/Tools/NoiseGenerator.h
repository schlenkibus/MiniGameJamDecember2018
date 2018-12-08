#pragma once
#include <vector>

struct NoiseGenerator {
    static std::vector<int>
    generateValues(std::uint32_t seed, unsigned long count, int height, int octaveCount, float frequency);
    static std::vector<int> generateWater(int width);
    static int interpolate(int a, int b, int x);
};


