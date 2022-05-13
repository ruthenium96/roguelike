#ifndef ARCH_ROGUELIKE_RANDOMNUMBERGENERATOR_H
#define ARCH_ROGUELIKE_RANDOMNUMBERGENERATOR_H

#include <random>

namespace world {
// static class for generating of random numbers.
class RandomNumberGenerator {
public:
    static float generate() {
        return distribution_(randomEngine_);
    }
private:
    inline static std::random_device rd;
    inline static std::default_random_engine randomEngine_ = std::default_random_engine (rd());
    inline static std::uniform_real_distribution<float> distribution_ = std::uniform_real_distribution<float>(0, 1);

};
}

#endif //ARCH_ROGUELIKE_RANDOMNUMBERGENERATOR_H
