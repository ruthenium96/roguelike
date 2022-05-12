#pragma once

#include "../../common/Command.h"

namespace controller::input {
// This is an abstract class to work with different possible input devices.
class AbstractManager {
  public:
    virtual common::ControllerCommand readCommand() = 0;
    virtual ~AbstractManager() = default;
};
}  // namespace controller::input
