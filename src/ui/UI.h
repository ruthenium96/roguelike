#ifndef ARCH_ROGUELIKE_UI_H
#define ARCH_ROGUELIKE_UI_H

#include "../common/Command.h"
#include "../common/WorldUITransfer.h"
#include "console_display.h"
#include "game_object_style.h"
#include <memory>

namespace ui {

namespace {

struct UiState {
    size_t inventory_pos{0};
    bool inventory_active{false};
};

}  // namespace

class UI {
  public:
    UI(const std::string& style = "default");  // TODO: add style set

    // draw current game image
    void draw(const common::WorldUITransfer& world_state);

    common::ControllerCommand apply_command(const common::ControllerCommand& command,
                                            const common::WorldUITransfer& world_state);
    // true if state was activated
    bool activate_state(const common::WorldUITransfer& world_state);
    void deactivate_state(const common::WorldUITransfer& world_state);

  private:
    // pushes hello line on display
    void pushHelloOnDisplay();

    // pushes the stats about game and player on display
    void pushStatsOnDisplay(const common::PlayerMetrics& player_stats);

    // pushes the current map on display
    void pushMapOnDisplay(const common::Map& map);

    // pushes player inventory on display
    void pushInventoryOnDisplay(const common::Inventory& inventory);

    // pushes message on display
    void pushMessageOnDisplay(const std::optional<std::string>& mbMessage);

  private:
    std::unique_ptr<IStyle> style_;

    // use shared_ptr?
    ConsoleDisplay display_;

    // state of UI (now only inventory)
    UiState state_;
};

}  // namespace ui

#endif  // ARCH_ROGUELIKE_UI_H
