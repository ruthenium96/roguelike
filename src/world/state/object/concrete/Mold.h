#ifndef ARCH_ROGUELIKE_MOLD_H
#define ARCH_ROGUELIKE_MOLD_H

#include "../AbstractObject.h"

namespace world::state::object {
class Mold : public AbstractObject {
  public:
    explicit Mold(const Identity& identity);
    common::ObjectType getObjectType() const override;
};
}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_MOLD_H
