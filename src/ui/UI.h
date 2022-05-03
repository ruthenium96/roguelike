#ifndef ARCH_ROGUELIKE_UI_H
#define ARCH_ROGUELIKE_UI_H

#include "../common/WorldUITransfer.h"
#include "console_display.h"
#include "game_object_style.h"
#include <memory>

namespace ui {

class UI {
  public:
    UI(const std::string& style = "default");  // TODO: add style set

    // draw current game image
    void draw(const common::WorldUITransfer& world_state);

  private:
    // pushes hello line on display
    void pushHelloOnDisplay();

    // pushes the stats about game and player on display
    void pushStatsOnDisplay(const common::PlayerMetrics& player_stats);

    // pushes the current map on display
    void pushMapOnDisplay(const common::Map& map);

    // pushes player inventory on display
    void pushInventoryOnDisplay(const common::Inventory& inventory);

  private:
    std::unique_ptr<IStyle> style_;

    // use shared_ptr?
    ConsoleDisplay display_;
};

}  // namespace ui

#endif  // ARCH_ROGUELIKE_UI_H
