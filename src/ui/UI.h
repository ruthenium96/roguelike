#ifndef ARCH_ROGUELIKE_UI_H
#define ARCH_ROGUELIKE_UI_H

#include "../common/Map.h"
#include "game_object_style.h"
#include "console_display.h"

#include <memory>

namespace ui 
{

class UI {
public:
    UI() {
        style_ = std::make_unique<DefaultStyle>();
    }

    void drawMap(const common::Map& map);

private:
    std::unique_ptr<IStyle> style_{nullptr}; 

    // make unique_ptr
    ConsoleDisplay display_;
};

} // namespace ui

#endif //ARCH_ROGUELIKE_UI_H
