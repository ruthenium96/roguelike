#ifndef ARCH_ROGUELIKE_ENGINE_H
#define ARCH_ROGUELIKE_ENGINE_H

#include "../common/Command.h"
#include "../common/WorldUITransfer.h"
#include "generator/AbstractGenerator.h"
#include "state/State.h"
#include <memory>

namespace world {

// Engine corresponds for interaction of World with other modules.
class Engine {
  public:
    Engine();
    // Applies Command
    common::Command applyCommand(const common::Command&);

    // Generate current Map
    common::WorldUITransfer getWorldUITransfer() const;

    void resetWorld();

  private:
    void initialize();
    void generateWorldAroundPlayer(common::Coordinate playerCoordinate);

    bool checkIfPlayerIsAlive() const;

    std::optional<std::shared_ptr<state::action::AbstractAction>> generateExternalAction(const common::Command&) const;

    state::State state_;
    std::unique_ptr<generator::AbstractGenerator> generator_;
    mutable std::optional<std::string> errorMessageForUi;
    void generateErrorMessageForUI(const common::Command&);
};

}  // namespace world

#endif  // ARCH_ROGUELIKE_ENGINE_H
