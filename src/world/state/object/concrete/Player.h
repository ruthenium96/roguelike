#ifndef ARCH_ROGUELIKE_PLAYER_H
#define ARCH_ROGUELIKE_PLAYER_H

#include "../AbstractObject.h"

namespace world::state::object {

class Player : public AbstractObject {
public:
    explicit Player(Identity&& identity);;
    common::ObjectType getObjectType() const override;
private:
};

}

#endif //ARCH_ROGUELIKE_PLAYER_H
