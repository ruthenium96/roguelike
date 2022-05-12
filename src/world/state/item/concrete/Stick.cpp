#include "Stick.h"

namespace world::state::item {
Stick::Stick(const world::state::Identity &itemIdentity,
             const world::state::Identity &objectHolderIdentity) : AbstractItem(itemIdentity, objectHolderIdentity) {
    setProperty("dattack", std::make_any<int32_t>(1));
}
}