#include <cassert>
#include "Confuse.h"
#include "../instant/Move.h"
#include "../../../RandomNumberGenerator.h"

namespace world::state::action {

Confuse::Confuse(const std::optional<Identity> &selfIdentity, Identity confusedObjectIdentity, int32_t duration,
                 object::Observer &objectObserver, Observer &actionObserver) : AbstractNPC(selfIdentity) {
    setProperty("every_turn", std::make_any<bool>(true));
    setProperty("duration", std::make_any<int32_t>(duration));
    setCorrespondingObjectIdentity(confusedObjectIdentity);

    std::optional<Identity> mbPreviousConfusingIdentity = std::nullopt;

    // deactivate all actions of confused object
    for (auto& action : actionObserver.getActionsByCorrespondingObjectIdentity(confusedObjectIdentity)) {
        // try to find previous confusing actions:
        if (action->getActionType() == ActionType::CONFUSE) {
            assert(!mbPreviousConfusing.has_value());
            mbPreviousConfusingIdentity = action->getSelfIdentity().value();
        }
        if (action->getProperty("every_turn").has_value()) {
            action->setProperty("every_turn", false);
        }
    }
    // delete previous confusing actions, if it was found
    if (mbPreviousConfusingIdentity.has_value()) {
        actionObserver.deleteAction(mbPreviousConfusingIdentity.value());
    }
}


bool Confuse::precondition(const object::Observer &objectObserver, const Observer &actionObserver) {
    return true;
}

void Confuse::changeTarget(object::Observer &objectObserver, Observer &actionObserver) {

    auto confusedObjectIdentity = getCorrespondingObjectIdentity().value();
    auto confusedObject = objectObserver.getObject(confusedObjectIdentity).value();
    auto hp = std::any_cast<int32_t>(confusedObject->getProperty("hp").value());
    if (hp <= 0) {
        death(objectObserver, actionObserver);
        return;
    }

    // random move
    int32_t dx_step_try = 0;
    int32_t dy_step_try = 0;
    randomDirection(dx_step_try, dy_step_try);
    auto move = std::make_shared<Move>(confusedObjectIdentity, dx_step_try, dy_step_try);
    if (move->precondition(objectObserver, actionObserver)) {
        move->changeTarget(objectObserver, actionObserver);
    }

    auto duration = std::any_cast<int32_t>(getProperty("duration").value());
    --duration;
    setProperty("duration", std::make_any<int32_t>(duration));
    if (duration <= 0) {
        for (auto& action : actionObserver.getActionsByCorrespondingObjectIdentity(confusedObjectIdentity)) {
            // turn on previous every_turn actions...
            if (action->getProperty("every_turn").has_value()) {
                action->setProperty("every_turn", true);
            }
        }
        deleteItselfFromActionObserver(actionObserver);
    }
}

void Confuse::randomDirection(int32_t &dx_step_try, int32_t &dy_step_try) {
    float probability = RandomNumberGenerator::generate();
    if (probability < 0.25) {
        dx_step_try = 1;
    }
    if (0.25 <= probability && probability < 0.50) {
        dx_step_try = -1;
    }
    if (0.50 <= probability && probability < 0.75) {
        dy_step_try = 1;
    }
    if (0.75 < probability) {
        dy_step_try = -1;
    }
}

ActionType Confuse::getActionType() const {
    return ActionType::CONFUSE;
}

}