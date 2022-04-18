
# pragma once // TODO: use guards instead

#include <iostream>
#include <vector>

namespace ui 
{

class ConsoleDisplay {
public:
  ConsoleDisplay(std::ostream& os = std::cout);

  // print data without clear display
  void print() const;

  // Clear actual console, works only for std::cout
  void clear() const;

  // clear display and print data
  void draw() const;

  // get single tile/pixel of display 
  char& at(size_t height_i, size_t width_i);

  // clear the data buffer
  void clear_data();

  // current display height
  size_t height() const;

  // current display width
  size_t width() const;
  
private:
  size_t height_;
  size_t width_;
  
  // TODO: replace char to tile/pixel
  std::vector<std::vector<char>> data_;
  
  std::ostream& os_;
};

} // namespace ui 