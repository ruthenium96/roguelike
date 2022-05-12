#ifndef ARCH_ROGUELIKE_PLAYERMETRICS_H
#define ARCH_ROGUELIKE_PLAYERMETRICS_H

namespace common {
struct PlayerMetrics {
    int32_t hp;
    int32_t lvl;
    int32_t xp;
    int32_t attack;
    int32_t defence;
};
}  // namespace common

#endif  // ARCH_ROGUELIKE_PLAYERMETRICS_H
