#ifndef ARCH_ROGUELIKE_WORLDUITRANSFER_H
#define ARCH_ROGUELIKE_WORLDUITRANSFER_H

#include "Inventory.h"
#include "Map.h"
#include "PlayerMetrics.h"

namespace common {
struct WorldUITransfer {
    Map map;
    PlayerMetrics playerMetrics;
    Inventory inventory;
};
}  // namespace common

#endif  // ARCH_ROGUELIKE_WORLDUITRANSFER_H
