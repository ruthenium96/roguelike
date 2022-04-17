#pragma once

#include "AbstractManager.h"

#include <iostream>

namespace controller::input {
class KeyboardManager : public AbstractManager {
public:
    KeyboardManager() = default;
    common::Command readCommand() override;
    ~KeyboardManager() override = default;
};
}
