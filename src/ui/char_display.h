#ifndef ARCH_ROGUELIKE_DISPLAY_H
#define ARCH_ROGUELIKE_DISPLAY_H

#include <cassert>
#include <cstddef>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace ui {

class CharDisplay {
  public:
    CharDisplay(size_t height, size_t width) : height_{height}, width_{width} { clear_data(); }

    virtual size_t height() const { return height_; };
    virtual size_t width() const { return width_; };

    const char& at(size_t height_i, size_t width_i) const { return data_.at(height_i).at(width_i); }
    char& at(size_t height_i, size_t width_i) { return const_cast<char&>(std::as_const(*this).at(height_i, width_i)); }

    void clear_data() { data_ = std::vector<std::vector<char>>(height_, std::vector<char>(width_, ' ')); }

    // add data from virtual display
    void add_display_data(CharDisplay& display, size_t offset_height = 0, size_t offset_width = 0) {
        for (size_t i = 0; i != display.height(); ++i) {
            for (size_t j = 0; j != display.width(); ++j) {
                const size_t hi = offset_height + i;
                const size_t wi = offset_width + j;
                if (std::tie(hi, wi) < std::tie(height_, width_)) {
                    at(hi, wi) = display.at(i, j);
                }
            }
        }
    }

    virtual ~CharDisplay() = default;

    void put_line_hor(size_t offset_height = 0, size_t offset_width = 0, size_t length = 0, char line_char = '*') {
        for (size_t i = 0; i != length; ++i) {
            at(offset_height, offset_width + i) = line_char;
        }
    }

    void fill_border(char border_char = '*') {
        assert((height() >= 2) && (width() >= 2));

        for (size_t i = 0; i != width(); ++i) {
            at(0, i) = border_char;
            at(height() - 1, i) = border_char;
        }

        for (size_t i = 0; i != height(); ++i) {
            at(i, 0) = border_char;
            at(i, width() - 1) = border_char;
        }
    }

    void put_string(const std::string& str, size_t offset_height = 0, size_t offset_width = 0) {
        for (size_t i = 0; i != str.size(); ++i) {
            const size_t hi = offset_height;
            const size_t wi = offset_width + i;
            if (std::tie(hi, wi) < std::tie(height_, width_)) {
                at(hi, wi) = str[i];
            }
        }
    }

  protected:
    const auto& data() const { return data_; }
    auto& data() { return data_; }

  private:
    size_t height_;
    size_t width_;

    std::vector<std::vector<char>> data_{};
};

}  // namespace ui

#endif  // ARCH_ROGUELIKE_DISPLAY_H
