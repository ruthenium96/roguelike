
# pragma once // TODO: use guards instead

#include <iostream>
#include <vector>
#include <iterator>

namespace ui 
{

class ConsoleDisplay {
public:
  ConsoleDisplay(std::ostream& os = std::cout);

  void print() const;

  void clear() const;

  void draw() const;

  char& at(size_t height_i, size_t width_i);

  void clear_data();

  size_t height() const;
  size_t width() const;
  
private:
  size_t height_;
  size_t width_;
  
  // TODO: replace char to tile/pixel
  std::vector<std::vector<char>> data_;
  
  std::ostream& os_;
};

} // namespace ui 