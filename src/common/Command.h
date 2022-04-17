#ifndef ARCH_ROGUELIKE_COMMAND_H
#define ARCH_ROGUELIKE_COMMAND_H

// This class helps modules communicate each other.
namespace common {
enum InputCommand {
    MOVE_TOP,
    MOVE_LEFT,
    MOVE_BOTTOM,
    MOVE_RIGHT
};

class Command {
public:
    InputCommand inputCommand;

};
}

#endif //ARCH_ROGUELIKE_COMMAND_H
