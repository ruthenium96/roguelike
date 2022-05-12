#include "console_display.h"
#include <iterator>

namespace ui {

static constexpr size_t kDefaultConsoleWidth = 55;
static constexpr size_t kDefaultConsoleHeight = 30;

ConsoleDisplay::ConsoleDisplay(std::ostream& os) : CharDisplay{kDefaultConsoleHeight, kDefaultConsoleWidth}, os_{os} {}

void ConsoleDisplay::print() const {
    for (const auto& line : data()) {
        std::copy(line.begin(), line.end(), std::ostream_iterator<char>{os_, ""});
        os_ << "\n";
    }
    os_ << std::flush;
}

void ConsoleDisplay::clear() const {
#ifdef _WIN32
    system("cls");
#else  // __linux__ or __APPLE__
    system("clear");
#endif
}

void ConsoleDisplay::draw() const {
    clear();
    print();
}

}  // namespace ui