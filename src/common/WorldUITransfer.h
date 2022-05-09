#ifndef ARCH_ROGUELIKE_WORLDUITRANSFER_H
#define ARCH_ROGUELIKE_WORLDUITRANSFER_H

#include <optional>
#include "Inventory.h"
#include "Map.h"
#include "PlayerMetrics.h"

namespace common {
struct WorldUITransfer {
    Map map;
    PlayerMetrics playerMetrics;
    Inventory inventory;
    std::optional<std::string> message;
};
}  // namespace common

#endif  // ARCH_ROGUELIKE_WORLDUITRANSFER_H
