#include "MoldEveryTurn.h"
#include "../../../RandomNumberGenerator.h"
#include "../../object/concrete/Mold.h"
#include "MoldInteraction.h"

namespace world::state::action {

MoldEveryTurn::MoldEveryTurn(const std::optional<Identity>& selfIdentity) : AbstractAction(selfIdentity) {
    setProperty("every_turn", true);
}

ActionType MoldEveryTurn::getActionType() const {
    return ActionType::MOLD_EVERY_TURN;
}

bool MoldEveryTurn::precondition(const object::Observer& objectObserver, const action::Observer& actionObserver) {
    auto moldObjectIdentity = getCorrespondingObjectIdentity().value();
    auto moldObject = objectObserver.getObject(moldObjectIdentity).value();
    auto moldCoordinate = moldObject->getCoordinate();
    auto onTopObjects = objectObserver.getObjectsAtCoordinate(moldCoordinate);
    for (const auto& object : onTopObjects) {
        if (object->getProperty("hp").has_value()) {
            // if it can cause damage:
            return true;
        }
    }
    std::vector<common::Coordinate> neighborCoordinates;
    neighborCoordinates.push_back({moldCoordinate.x + 1, moldCoordinate.y});
    neighborCoordinates.push_back({moldCoordinate.x - 1, moldCoordinate.y});
    neighborCoordinates.push_back({moldCoordinate.x, moldCoordinate.y + 1});
    neighborCoordinates.push_back({moldCoordinate.x, moldCoordinate.y - 1});

    for (auto coordinate : neighborCoordinates) {
        auto objects = objectObserver.getObjectsAtCoordinate(coordinate);
        bool wasHereMold = false;
        bool wasBlocking = false;
        for (auto& object : objects) {
            if (object->getProperty("blocking").has_value()) {
                // cannot grow to wall
                wasBlocking = true;
            }
            if (object->getObjectType() == common::ObjectType::MOLD) {
                // cannot grow if there is already mold
                wasHereMold = true;
            }
        }
        if (!wasBlocking && !wasHereMold) {
            // if it can grow
            return true;
        }
    }
    return false;
}

void MoldEveryTurn::changeTarget(object::Observer& objectObserver, action::Observer& actionObserver) {
    auto moldObjectIdentity = getCorrespondingObjectIdentity().value();
    auto moldObject = objectObserver.getObject(moldObjectIdentity).value();
    auto moldCoordinate = moldObject->getCoordinate();
    // attack part
    auto onTopObjects = objectObserver.getObjectsAtCoordinate(moldCoordinate);
    for (auto& object : onTopObjects) {
        if (object->getProperty("hp").has_value()) {
            attack(moldObject, object);
        }
    }
    // growing part
    std::vector<common::Coordinate> neighborCoordinates;
    neighborCoordinates.push_back({moldCoordinate.x + 1, moldCoordinate.y});
    neighborCoordinates.push_back({moldCoordinate.x - 1, moldCoordinate.y});
    neighborCoordinates.push_back({moldCoordinate.x, moldCoordinate.y + 1});
    neighborCoordinates.push_back({moldCoordinate.x, moldCoordinate.y - 1});

    for (auto coordinate : neighborCoordinates) {
        auto objects = objectObserver.getObjectsAtCoordinate(coordinate);
        bool wasHereMold = false;
        bool wasBlocking = false;
        for (auto& object : objects) {
            if (object->getProperty("blocking").has_value()) {
                // cannot grow to wall
                wasBlocking = true;
            }
            if (object->getObjectType() == common::ObjectType::MOLD) {
                // cannot grow if there is already mold
                wasHereMold = true;
            }
        }
        if (!wasBlocking && !wasHereMold) {
            // if it can grow
            float probability = RandomNumberGenerator::generate();
            auto growingThreshold = std::any_cast<float>(moldObject->getProperty("growingThreshold").value());
            if (probability > growingThreshold) {
                grow(objectObserver, actionObserver, coordinate);
            }
        }
    }
}

void MoldEveryTurn::grow(object::Observer& objectObserver,
                         Observer& actionObserver,
                         common::Coordinate wantedCoordinate) {
    auto moldObjectIdentity = getCorrespondingObjectIdentity().value();
    auto moldObject = objectObserver.getObject(moldObjectIdentity).value();
    std::shared_ptr<AbstractAction> thisMoldInteraction = nullptr;
    for (auto& action : actionObserver.getActionsByCorrespondingObjectIdentity(moldObjectIdentity)) {
        if (action->getProperty("interaction").has_value() &&
            std::any_cast<bool>(action->getProperty("interaction").value())) {
            thisMoldInteraction = action;
            break;
        }
    }

    // every growing makes mold stronger:
    auto old_attack = std::any_cast<int32_t>(moldObject->getProperty("attack").value());
    moldObject->setProperty("attack", old_attack + 1);

    // deep clone of Mold Object:
    auto cloneMoldObjectIdentity = IdentityGenerator::getNewIdentity();
    auto cloneMoldObject = std::make_shared<object::Mold>(cloneMoldObjectIdentity);
    for (const auto& [key, value] : moldObject->getAllProperties()) {
        cloneMoldObject->setProperty(key, value);
    }
    cloneMoldObject->getCoordinate() = wantedCoordinate;

    // deep clone of Mold Actions
    // Every turn
    auto cloneMoldEveryTurnIdentity = IdentityGenerator::getNewIdentity();
    auto cloneMoldEveryTurn = std::make_shared<MoldEveryTurn>(cloneMoldEveryTurnIdentity);
    cloneMoldEveryTurn->setCorrespondingObjectIdentity(cloneMoldObjectIdentity);
    for (const auto& [key, value] : getAllProperties()) {
        cloneMoldEveryTurn->setProperty(key, value);
    }
    // Interaction
    auto cloneMoldInteractionIdentity = IdentityGenerator::getNewIdentity();
    auto cloneMoldInteraction = std::make_shared<MoldInteraction>(cloneMoldInteractionIdentity);
    cloneMoldInteraction->setCorrespondingObjectIdentity(cloneMoldObjectIdentity);
    for (const auto& [key, value] : thisMoldInteraction->getAllProperties()) {
        cloneMoldInteraction->setProperty(key, value);
    }

    objectObserver.addObject(cloneMoldObject);
    actionObserver.addAction(cloneMoldEveryTurn);
    actionObserver.addAction(cloneMoldInteraction);
}

}  // namespace world::state::action