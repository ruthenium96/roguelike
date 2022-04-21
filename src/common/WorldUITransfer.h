#ifndef ARCH_ROGUELIKE_WORLDUITRANSFER_H
#define ARCH_ROGUELIKE_WORLDUITRANSFER_H

#include "Map.h"
#include "PlayerMetrics.h"
#include "Inventory.h"

namespace common {
struct WorldUITransfer {
    Map map;
    PlayerMetrics playerMetrics;
    Inventory inventory;
};
}

#endif //ARCH_ROGUELIKE_WORLDUITRANSFER_H
