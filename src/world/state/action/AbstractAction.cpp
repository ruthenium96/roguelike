#include "AbstractAction.h"

namespace world::state::action {
void AbstractAction::deleteItselfFromActionObserver(action::Observer& actionObserver) {
    actionObserver.deleteAction(getSelfIdentity().value());
}
}  // namespace world::state::action