#include "AbstractGenerator.h"
#include "../../common/ItemType.h"
#include "../state/action/internal/Poison.h"
#include "../state/action/internal/PickDropItem.h"
#include "../state/action/npc/AggressiveNPC.h"
#include "../state/action/npc/InactiveNPC.h"
#include "../state/action/npc/CowardNPC.h"
#include "../state/item/concrete/Ring.h"
#include "../state/item/concrete/Stick.h"
#include "../state/object/concrete/Artefact.h"
#include "../state/object/concrete/Wall.h"
#include "../state/object/concrete/NPC.h"
#include <random>
#include <stdexcept>

namespace world::generator {

void AbstractGenerator::addPlayer(common::Coordinate coordinate,
                                  std::vector<ObjectAndActions>& answer) {
    ObjectAndActions player;
    auto playerIdentity = state::IdentityGenerator::getNewIdentity();
    // add Player object
    player.object = std::make_shared<state::object::Player>(playerIdentity);
    player.object->getCoordinate() = coordinate;
    // add Player actions
    auto actionIdentity = state::IdentityGenerator::getNewIdentity();
    auto poisonAction = std::make_shared<state::action::Poison>(actionIdentity, -1, 100000);
    poisonAction->setCorrespondingObjectIdentity(playerIdentity);
    player.actions.push_back(poisonAction);
    // ...
    answer.push_back(player);
}

void AbstractGenerator::addFloor(common::Coordinate coordinate,
                                 std::vector<ObjectAndActions>& answer) {
    // add Floor
    ObjectAndActions floor;
    floor.object = std::make_shared<state::object::Floor>(state::IdentityGenerator::getNewIdentity());
    floor.object->getCoordinate() = coordinate;
    // add no Floor actions
    // ...
    answer.push_back(floor);
}

void AbstractGenerator::addWall(common::Coordinate coordinate,
                                std::vector<ObjectAndActions>& answer) {
    // add Wall
    ObjectAndActions wall;
    wall.object = std::make_shared<state::object::Wall>(state::IdentityGenerator::getNewIdentity());
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
                                    std::array<float, 1> threshold) {
    // add Artefact
    ObjectAndActions artefact;
    auto objectIdentity = state::IdentityGenerator::getNewIdentity();
    artefact.object = std::make_shared<state::object::Artefact>(objectIdentity);
    artefact.object->getCoordinate() = coordinate;
    // add Artefact item
    auto itemIdentity = state::IdentityGenerator::getNewIdentity();

    float probability = distribution_(randomEngine_);
    if (probability > threshold[0]) {
        artefact.object->getItems().push_back(std::make_unique<world::state::item::Ring>(itemIdentity, objectIdentity));
    } else {
        artefact.object->getItems().push_back(std::make_unique<world::state::item::Stick>(itemIdentity, objectIdentity));
    }

    // add Artefact actions
    auto actionIdentity = state::IdentityGenerator::getNewIdentity();
    auto actionOnInteraction = std::make_shared<state::action::PickDropItem>(actionIdentity);
    actionOnInteraction->setCorrespondingItemIdentity(itemIdentity);
    actionOnInteraction->setCorrespondingObjectIdentity(objectIdentity);
    artefact.actions.push_back(actionOnInteraction);

    answer.push_back(artefact);
}

void AbstractGenerator::addArtefact(common::Coordinate coordinate,
                                    std::vector<ObjectAndActions>& answer) {
    std::array<float, 1> defaultThreshold = {0.8};
    addArtefact(coordinate, answer, defaultThreshold);
}

void AbstractGenerator::addNPC(common::Coordinate coordinate,
                               std::vector<ObjectAndActions>& answer,
                               std::array<float, 2> threshold) {
    ObjectAndActions npc;
    auto npcIdentity = state::IdentityGenerator::getNewIdentity();
    // add NPC object
    npc.object = std::make_shared<state::object::NPC>(npcIdentity);
    npc.object->getCoordinate() = coordinate;
    // add NPC actions
    auto actionIdentity = state::IdentityGenerator::getNewIdentity();
    std::shared_ptr<state::action::AbstractNPC> NPCAction = nullptr;
    float probability = distribution_(randomEngine_);
    if (probability > threshold[0]) {
        NPCAction = std::make_shared<world::state::action::AggressiveNPC>(actionIdentity);
    } else if (probability > threshold[1]) {
        NPCAction = std::make_shared<world::state::action::CowardNPC>(actionIdentity);
    } else {
        NPCAction = std::make_shared<world::state::action::InactiveNPC>(actionIdentity);
    }

    NPCAction->setCorrespondingObjectIdentity(npcIdentity);
    npc.actions.push_back(NPCAction);
    // ...
    answer.push_back(npc);
}

void AbstractGenerator::addNPC(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
    std::array<float, 2> defaultThreshold = {0.5, 0.1};
    addNPC(coordinate, answer, defaultThreshold);
}


const serialization::Serializer &AbstractGenerator::getSaver() const {
    return saver_;
}

AbstractGenerator::AbstractGenerator() {
    std::random_device rd;
    randomEngine_ = std::default_random_engine (rd());
    distribution_ = std::uniform_real_distribution<float>(0, 1);
}
}  // namespace world::generator