#include "KeyboardManager.h"

#include <iostream>
#include <chrono>

namespace {
// this function takes a character from the console without confirmation
#ifdef linux

#include <termios.h>
#include <unistd.h>
#include <cstdio>

#include "../../common/Command.h"

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
}


namespace controller::input {
common::ControllerCommand KeyboardManager::readCommand() {
    char symbol = std::tolower(read_char_with_no_confirmation());
    if (symbol == 'w') {
        return common::ControllerCommand::MOVE_TOP;
    } else if (symbol == 'd') {
        return common::ControllerCommand::MOVE_RIGHT;
    } else if (symbol == 's') {
        return common::ControllerCommand::MOVE_BOTTOM;
    } else if (symbol == 'a') {
        return common::ControllerCommand::MOVE_LEFT;
    } else if (symbol == 'q') {
        return common::ControllerCommand::EXIT;
    } else if (symbol == 'e') {
        return common::ControllerCommand::INTERACT;
    } else {
        return common::ControllerCommand::UNKNOWN;
    }
}
}