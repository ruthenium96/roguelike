
#pragma once  // TODO: use guards instead

#include "char_display.h"
#include <iostream>
#include <vector>

namespace ui {

class ConsoleDisplay : public CharDisplay {
  public:
    explicit ConsoleDisplay(std::ostream& os = std::cout);

    // print data without clear display
    void print() const;

    // Clear actual console, works only for std::cout
    void clear() const;

    // clear display and print data
    void draw() const;

  private:
    std::ostream& os_;
};

}  // namespace ui