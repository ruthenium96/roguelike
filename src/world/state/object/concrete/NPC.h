#ifndef ARCH_ROGUELIKE_NPC_H
#define ARCH_ROGUELIKE_NPC_H

#include "../AbstractObject.h"

namespace world::state::object {
class NPC : public AbstractObject {
  public:
    explicit NPC(const Identity& identity);
    common::ObjectType getObjectType() const override;
};
}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_NPC_H
