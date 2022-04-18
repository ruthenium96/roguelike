#ifndef ARCH_ROGUELIKE_UI_H
#define ARCH_ROGUELIKE_UI_H

#include "../common/Map.h"
#include "../world/Engine.h"
#include "game_object_style.h"
#include "console_display.h"

#include <memory>

namespace ui 
{

class UI {
public:
    UI(const world::Engine& engine);

    void draw() const;

    // current stats type is stub
    void drawStatsOnDisplay(int32_t stats) const;
    
    void drawMapOnDisplay(const common::Map& map) const;

private:
    std::unique_ptr<IStyle> style_{nullptr}; 

    // TODO: make unique_ptr
    mutable ConsoleDisplay display_;

    // Think about it
    const world::Engine& engine_;
};

} // namespace ui

#endif // ARCH_ROGUELIKE_UI_H
