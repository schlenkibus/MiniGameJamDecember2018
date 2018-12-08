#include <random>
#include <iostream>
#include "NoiseGenerator.h"
#include "PerlinNoise.hpp"

std::vector<int>
NoiseGenerator::generateValues(std::uint32_t seed, unsigned long count, int height, int octaveCount, float frequency) {
    std::vector<int> ret;
    ret.reserve(count);

    const siv::PerlinNoise noise(seed);

    const auto fx = count / frequency;
    for(int i = 0; i < count; i++) {
        const auto y = noise.octaveNoise(i / fx, octaveCount);
        ret.push_back(static_cast<int>(y * height));
    }
    std::cout << std::endl;

    return ret;
}

std::vector<int>
NoiseGenerator::generateWater(int width) {
    std::vector<int> ret;
    ret.reserve(static_cast<unsigned long>(width));

    const siv::PerlinNoise noise(std::uint32_t(187187187));

    const auto fx = width / 10.;
    for(int i = 0; i < width; i++) {
        const auto y = noise.octaveNoise(i / fx, 4);
        ret.push_back(static_cast<int>(y * 30));
    }

    return ret;
}

int NoiseGenerator::interpolate(int a, int b, int x) {
    auto ft = x * M_PI;
    auto f = (1 - std::cos(ft)) * 0.5;
    return static_cast<int>(a * (1 - f) + b * f);
}
