#ifndef ARCH_ROGUELIKE_WALL_H
#define ARCH_ROGUELIKE_WALL_H

#include "../AbstractObject.h"

namespace world::state::object
{
class Wall : public AbstractObject
{
  public:
    explicit Wall(Identity&& identity) : AbstractObject(std::move(identity)){};
    common::ObjectType getObjectType() const override;
};
}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_WALL_H
