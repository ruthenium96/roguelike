#ifndef ARCH_ROGUELIKE_ENGINE_H
#define ARCH_ROGUELIKE_ENGINE_H

#include "../common/Command.h"
#include "../common/WorldUITransfer.h"
#include "generator/AbstractGenerator.h"
#include "state/State.h"
#include <memory>

namespace world
{

// Engine corresponds for interaction of World with other modules.
class Engine
{
  public:
    Engine();
    // Applies ControllerCommand
    void applyCommand(const common::ControllerCommand&);

    // Generate current Map
    common::WorldUITransfer getWorldUITransfer() const;

  private:
    void generateWorldAroundPlayer(common::Coordinate playerCoordinate);

    state::State state_;
    std::unique_ptr<generator::AbstractGenerator> generator_;
};

}  // namespace world

#endif  // ARCH_ROGUELIKE_ENGINE_H
