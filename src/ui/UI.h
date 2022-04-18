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
    UI(const world::Engine& engine)
        : engine_{engine}
    {
        style_ = std::make_unique<DefaultStyle>();
    }

    void draw() const {
        drawStatsOnDisplay(engine_.getStats());
        drawMapOnDisplay(engine_.getMap());
        display_.draw();
    }

    // current type is stub now
    void drawStatsOnDisplay(int32_t stats) const;
    
    void drawMapOnDisplay(const common::Map& map) const;

private:
    std::unique_ptr<IStyle> style_{nullptr}; 

    // make unique_ptr
    mutable ConsoleDisplay display_;

    const world::Engine& engine_;
};

} // namespace ui

#endif //ARCH_ROGUELIKE_UI_H
