#include "KeyboardManager.h"
#include <chrono>
#include <iostream>
#include <stdexcept>

namespace {
// this function takes a character from the console without confirmation
#ifdef __linux__

#include "../../common/Command.h"
#include <termios.h>
#include <unistd.h>
#include <cstdio>

inline char read_char_with_no_confirmation() {
    termios oldattr{};
    termios newattr{};
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return static_cast<char>(ch);
}

#elif _WIN32
#include <conio.h>

inline char read_char_with_no_confirmation() {
    return getch();
}

#else
inline char read_char_with_no_confirmation() {
    throw std::runtime_error("Platform doesn't support");
}
#endif
}  // namespace

namespace controller::input {
using common::ControllerCommand;

ControllerCommand KeyboardManager::readCommand() {
    char symbol = std::tolower(read_char_with_no_confirmation());
    if (symbol == 'w') {
        return ControllerCommand::MOVE_TOP;
    } else if (symbol == 'd') {
        return ControllerCommand::MOVE_RIGHT;
    } else if (symbol == 's') {
        return ControllerCommand::MOVE_BOTTOM;
    } else if (symbol == 'a') {
        return ControllerCommand::MOVE_LEFT;
    } else if (symbol == 'q') {
        return ControllerCommand::EXIT;
    } else if (symbol == 'e') {
        return ControllerCommand::INTERACT;

    } else if (symbol == 'r') {
        return ControllerCommand::UI_ACTIVATE_INVENTORY;
    } else if (symbol == 'g') {
        return ControllerCommand::UI_INVENTORY_DOWN;
    } else if (symbol == 't') {
        return ControllerCommand::UI_INVENTORY_UP;
    } else if (symbol == 'f') {
        return ControllerCommand::UI_INVENTORY_APPLY;

    } else {
        return ControllerCommand::UNKNOWN;
    }

    throw std::runtime_error("ControllerCommand was not generated");
}
}  // namespace controller::input