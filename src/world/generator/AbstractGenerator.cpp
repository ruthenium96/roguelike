#include "AbstractGenerator.h"
#include "../RandomNumberGenerator.h"
#include "../../common/ItemType.h"
#include "../state/action/internal/Poison.h"
#include "../state/action/internal/PickDropItem.h"
#include "../state/action/npc/AggressiveNPC.h"
#include "../state/action/npc/InactiveNPC.h"
#include "../state/action/npc/CowardNPC.h"
#include "../state/action/mold/MoldInteraction.h"
#include "../state/action/mold/MoldEveryTurn.h"
#include "../state/item/concrete/Ring.h"
#include "../state/item/concrete/Stick.h"
#include "../state/object/concrete/Artefact.h"
#include "../state/object/concrete/Wall.h"
#include "../state/object/concrete/NPC.h"
#include "../state/object/concrete/Mold.h"
#include <random>

namespace world::generator {

void AbstractGenerator::addPlayer(common::Coordinate coordinate,
                                  std::vector<ObjectAndActions>& answer) {
    ObjectAndActions player;
    auto playerIdentity = state::IdentityGenerator::getNewIdentity();
    // add Player object
    player.object = std::make_shared<state::object::Player>(playerIdentity);
    player.object->getCoordinate() = coordinate;
    // add Player actions
//    auto actionIdentity = state::IdentityGenerator::getNewIdentity();
//    auto poisonAction = std::make_shared<state::action::Poison>(actionIdentity, -1, 100000);
//    poisonAction->setCorrespondingObjectIdentity(playerIdentity);
//    player.actions.push_back(poisonAction);
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

    float probability = RandomNumberGenerator::generate();
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
    addArtefact(coordinate, answer, artefactTypeProbability_);
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
    float probability = RandomNumberGenerator::generate();

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
    addNPC(coordinate, answer, NPCTypeProbability_);
}

void AbstractGenerator::addMold(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
    ObjectAndActions mold;
    auto moldIdentity = state::IdentityGenerator::getNewIdentity();
    // add NPC object
    mold.object = std::make_shared<state::object::Mold>(moldIdentity);
    mold.object->getCoordinate() = coordinate;
    // add Mold actions
    auto moldEveryTurn = std::make_shared<state::action::MoldEveryTurn>(state::IdentityGenerator::getNewIdentity());
    moldEveryTurn->setCorrespondingObjectIdentity(moldIdentity);
    mold.actions.push_back(moldEveryTurn);

    auto moldInteraction = std::make_shared<state::action::MoldInteraction>(state::IdentityGenerator::getNewIdentity());
    moldInteraction->setCorrespondingObjectIdentity(moldIdentity);
    mold.actions.push_back(moldInteraction);
    // ...
    answer.push_back(mold);
}


const serialization::Serializer &AbstractGenerator::getSaver() const {
    return saver_;
}

}  // namespace world::generator