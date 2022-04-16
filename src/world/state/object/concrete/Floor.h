#ifndef ARCH_ROGUELIKE_FLOOR_H
#define ARCH_ROGUELIKE_FLOOR_H

#include "../AbstractObject.h"

namespace world::state::object {
class Floor : public AbstractObject {
public:
    explicit Floor(Identity&& identity) : AbstractObject(std::move(identity)) {};
private:

};
}

#endif //ARCH_ROGUELIKE_FLOOR_H
