#include "KeyboardManager.h"

#include <iostream>
#include <chrono>

namespace {
// this function takes a character from the console without confirmation
#ifdef linux

#include <termios.h>
#include <unistd.h>
#include <cstdio>

char read_char_with_no_confirmation() {
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

char read_char_with_no_confirmation() {
    return getch();
}

#else
char read_char_with_no_confirmation() {
    throw std::runtime_error("Platform doesn't support");
}
#endif
}


namespace controller::input {
common::Command KeyboardManager::readCommand() {
    char c;
    while (c = read_char_with_no_confirmation()) {
        std::cout << c << std::endl;
    }
    return {};
}
}