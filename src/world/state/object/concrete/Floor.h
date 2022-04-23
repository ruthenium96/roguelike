#ifndef ARCH_ROGUELIKE_FLOOR_H
#define ARCH_ROGUELIKE_FLOOR_H

#include "../AbstractObject.h"

namespace world::state::object {
class Floor : public AbstractObject {
public:
    explicit Floor(const Identity& identity) : AbstractObject(identity) {};
    common::ObjectType getObjectType() const override;

  private:
};
}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_FLOOR_H
