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
    if (symbol == 'w' || symbol == 'd' || symbol == 's' || symbol == 'a') {
        common::Direction direction;
        if (symbol == 'w') {
            direction = common::Direction::TOP;
        } else if (symbol == 'd') {
            direction = common::Direction::RIGHT;
        } else if (symbol == 's') {
            direction = common::Direction::BOTTOM;
        } else if (symbol == 'a') {
            direction = common::Direction::LEFT;
        }
        return common::Move{direction};
    } else if (symbol == 'q') {
        return common::Controller_Exit();
    } else if (symbol == 'e') {
        return common::World_Interact();
    } else if (symbol == 'r') {
        return common::Controller_ChangeRegime();
    } else if (symbol == 'f') {
        return common::UI_ApplyItem();
    } else if (symbol == 'v') {
        return common::UI_DropItem();
    } else {
        return common::Controller_Unknown();
    }
}
}  // namespace controller::input