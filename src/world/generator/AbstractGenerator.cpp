#include "AbstractGenerator.h"
#include "../../common/ItemType.h"
#include "../state/action/concrete/Poison.h"
#include "../state/action/concrete/PickDropItem.h"
#include "../state/item/concrete/Ring.h"
#include "../state/item/concrete/Stick.h"
#include "../state/object/concrete/Artefact.h"
#include "../state/object/concrete/Wall.h"
#include <random>
#include <stdexcept>

namespace world::generator {

void AbstractGenerator::addPlayer(common::Coordinate coordinate,
                                  std::vector<ObjectAndActions>& answer,
                                  uint64_t& generated_identities_) {
    ObjectAndActions player;
    auto playerIdentity = state::Identity(generated_identities_++);
    // add Player object
    player.object = std::make_shared<state::object::Player>(playerIdentity);
    player.object->getCoordinate() = coordinate;
    // add Player actions
    auto actionIdentity = state::Identity(generated_identities_++);
    auto poisonAction = std::make_shared<state::action::Poison>(actionIdentity, -1, 100000);
    poisonAction->setCorrespondingObjectIdentity(playerIdentity);
    player.actions.push_back(poisonAction);
    // ...
    answer.push_back(player);
}

void AbstractGenerator::addFloor(common::Coordinate coordinate,
                                 std::vector<ObjectAndActions>& answer,
                                 uint64_t& generated_identities_) {
    // add Floor
    ObjectAndActions floor;
    floor.object = std::make_shared<state::object::Floor>(state::Identity(generated_identities_++));
    floor.object->getCoordinate() = coordinate;
    // add no Floor actions
    // ...
    answer.push_back(floor);
}

void AbstractGenerator::addWall(common::Coordinate coordinate,
                                std::vector<ObjectAndActions>& answer,
                                uint64_t& generated_identities_) {
    // add Wall
    ObjectAndActions wall;
    wall.object = std::make_shared<state::object::Wall>(state::Identity(generated_identities_++));
    wall.object->getCoordinate() = coordinate;
    // add no Wall actions
    // ...
    answer.push_back(wall);
}

namespace {
inline common::ItemType genItemType() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0, 1);

    float probability = distr(eng);
    if (probability > 0.8) {
        return common::ItemType::RING;
    } else {
        return common::ItemType::STICK;
    }
}
}  // namespace

void AbstractGenerator::addArtefact(common::Coordinate coordinate,
                                    std::vector<ObjectAndActions>& answer,
                                    uint64_t& generated_identities_) {
    // add Artefact
    ObjectAndActions artefact;
    auto objectIdentity = state::Identity(generated_identities_++);
    artefact.object = std::make_shared<state::object::Artefact>(objectIdentity);
    artefact.object->getCoordinate() = coordinate;
    // add Artefact item
    auto itemIdentity = state::Identity(generated_identities_++);

    auto generatedItemType = genItemType();
    switch (generatedItemType) {
        case common::ItemType::RING:
            artefact.object->getItems().push_back(
                std::make_unique<world::state::item::Ring>(itemIdentity, objectIdentity));
            break;
        case common::ItemType::STICK:
            artefact.object->getItems().push_back(
                std::make_unique<world::state::item::Stick>(itemIdentity, objectIdentity));
            break;
        default:
            throw std::runtime_error("Unknown item type was generated");
    }

    // add Artefact actions
    auto actionIdentity = state::Identity(generated_identities_++);
    auto actionOnInteraction = std::make_shared<state::action::PickDropItem>(actionIdentity);
    actionOnInteraction->setCorrespondingItemIdentity(itemIdentity);
    actionOnInteraction->setCorrespondingObjectIdentity(objectIdentity);
    artefact.actions.push_back(actionOnInteraction);

    answer.push_back(artefact);
}

const serialization::Serializer &AbstractGenerator::getSaver() const {
    return saver_;
}
}  // namespace world::generator