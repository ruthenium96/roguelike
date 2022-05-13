#pragma once

#include "AbstractManager.h"

namespace controller::input {
// Realization for keyboard.
class KeyboardManager : public AbstractManager {
  public:
    KeyboardManager() = default;
    common::Command readCommand() override;
};
}  // namespace controller::input
