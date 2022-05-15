#include "Ring.h"

namespace world::state::item {
Ring::Ring(const Identity& itemIdentity, const Identity& objectHolderIdentity)
    : AbstractItem(itemIdentity, objectHolderIdentity) {
    setProperty("ddefence", std::make_any<int32_t>(1));
}
}  // namespace world::state::item