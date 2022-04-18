
# pragma once // TODO: use guards instead

#include <iostream>
#include <vector>
#include <iterator>

namespace ui 
{

static constexpr size_t kConsoleWidth = 120;
static constexpr size_t kConsoleHeight = 30;



class ConsoleDisplay {
public:
  ConsoleDisplay()
    : width_{ kConsoleWidth }
    , height_ { kConsoleHeight}
    , os{std::cout}
  {
    clear_data();
  }

  void print() const {
    for (const auto& line : data_) {
      std::copy(line.begin(), line.end(), std::ostream_iterator<char>{ os, "" });
      os << "\n";
    }
    os << std::flush;
  }

  void clear() const {
#ifdef _WIN32
    system("cls");
#else // __linux__ or __APPLE__
    system("clear");
#endif
  }

  void display() const {
    clear();
    print();
  }

  char& at(size_t height_i, size_t width_i) {
    return data_.at(height_i).at(width_i);
  }

  void clear_data() {
    data_= std::vector<std::vector<char>>(
      height_, std::vector<char>(width_, ' '));
  }

  size_t width() const { return width_; }
  size_t height() const { return height_; }
  
private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<char>> data_;  // TODO: replace char to tile/pixel
  std::ostream& os;
};

} // namespace ui 