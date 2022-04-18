#pragma once

#include "AbstractManager.h"

namespace controller::input {
class KeyboardManager : public AbstractManager {
public:
    KeyboardManager() = default;
    common::ControllerCommand readCommand() override;
    ~KeyboardManager() override = default;
};
}
