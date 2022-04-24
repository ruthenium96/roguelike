#include "console_display.h"
#include <iterator>

namespace ui {

static constexpr size_t kDefaultConsoleWidth = 120;
static constexpr size_t kDefaultConsoleHeight = 30;

ConsoleDisplay::ConsoleDisplay(std::ostream& os)
    : height_{kDefaultConsoleHeight}, width_{kDefaultConsoleWidth}, os_{os} {
    clear_data();
}

void ConsoleDisplay::print() const {
    for (const auto& line : data_) {
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

char& ConsoleDisplay::at(size_t height_i, size_t width_i) {
    return data_.at(height_i).at(width_i);
}

void ConsoleDisplay::clear_data() {
    data_ = std::vector<std::vector<char>>(height_, std::vector<char>(width_, ' '));
}

size_t ConsoleDisplay::width() const {
    return width_;
}
size_t ConsoleDisplay::height() const {
    return height_;
}

}  // namespace ui