#include "AbstractGenerator.h"

#include "../state/object/concrete/Wall.h"
#include "../state/object/concrete/Artefact.h"
#include "../state/item/concrete/Stick.h"
#include "../state/action/concrete/PickItem.h"

namespace world::generator{

    void AbstractGenerator::addPlayer(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer, uint64_t& generated_identities_) {
        ObjectAndActions player;
        // add Player object
        player.object = std::make_shared<state::object::Player>(state::Identity(generated_identities_++));
        player.object->getCoordinate() = coordinate;
        // add no Player actions
        // ...
        answer.push_back(player);
    }

    void AbstractGenerator::addFloor(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer, uint64_t& generated_identities_) {
        // add Floor
        ObjectAndActions floor;
        floor.object = std::make_shared<state::object::Floor>(state::Identity(generated_identities_++));
        floor.object->getCoordinate() = coordinate;
        // add no Floor actions
        // ...
        answer.push_back(floor);
    }

    void AbstractGenerator::addWall(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer, uint64_t& generated_identities_) {
        // add Wall
        ObjectAndActions wall;
        wall.object = std::make_shared<state::object::Wall>(state::Identity(generated_identities_++));
        wall.object->getCoordinate() = coordinate;
        // add no Wall actions
        // ...
        answer.push_back(wall);
    }

    void AbstractGenerator::addArtefact(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer, uint64_t& generated_identities_) {
        // add Artefact
        ObjectAndActions artefact;
        auto objectIdentity = state::Identity(generated_identities_++);
        artefact.object = std::make_shared<state::object::Artefact>(objectIdentity);
        artefact.object->getCoordinate() = coordinate;
        // add Artefact item
        auto itemIdentity = state::Identity(generated_identities_++);
        artefact.object->getItems().push_back(std::make_unique<world::state::item::Stick>(itemIdentity, objectIdentity));
        // add Artefact actions
        auto actionIdentity = state::Identity(generated_identities_++);
        auto actionOnInteraction = std::make_shared<state::action::PickItem>(actionIdentity);
        actionOnInteraction->setCorrespondingItemIdentity(itemIdentity);
        actionOnInteraction->setCorrespondingObjectIdentity(objectIdentity);
        artefact.actions.push_back(actionOnInteraction);

        answer.push_back(artefact);
    }
}