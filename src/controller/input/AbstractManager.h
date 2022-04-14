#ifndef ARCH_ROGUELIKE_ABSTRACTMANAGER_H
#define ARCH_ROGUELIKE_ABSTRACTMANAGER_H

#include "../../common/Command.h"

namespace controller::input {
// This is an abstract class to work with different possible input devices.
class AbstractManager {
public:
    virtual common::Command readCommand() = 0;
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTMANAGER_H
