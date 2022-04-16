#ifndef ARCH_ROGUELIKE_ENGINE_H
#define ARCH_ROGUELIKE_ENGINE_H

#include <memory>

#include "state/State.h"
#include "generator/AbstractGenerator.h"

namespace world {
class Engine {
public:
    Engine();
    void start();

private:
    state::State state_;
    std::unique_ptr<generator::AbstractGenerator> generator_;
};
}

#endif //ARCH_ROGUELIKE_ENGINE_H
