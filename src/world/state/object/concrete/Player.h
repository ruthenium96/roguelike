#ifndef ARCH_ROGUELIKE_PLAYER_H
#define ARCH_ROGUELIKE_PLAYER_H

#include "../AbstractObject.h"

namespace world::state::object {

class Player : public AbstractObject {
  public:
    explicit Player(const Identity& identity);
    common::ObjectType getObjectType() const override;
};

}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_PLAYER_H
