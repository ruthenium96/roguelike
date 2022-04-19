#include "OnTheFly.h"
#include "../state/object/concrete/Wall.h"
#include "../state/object/concrete/Artefact.h"
#include "../state/item/concrete/Stick.h"
#include "../state/action/concrete/PickItem.h"
#include <random>
#include <algorithm>

namespace world::generator
{
    
std::vector<ObjectAndActions>
OnTheFly::generateObjects(common::Coordinate coordinate, const state::object::Observer&) {

    if (std::find(generated_coordinates_.begin(), generated_coordinates_.end(), coordinate) != generated_coordinates_.end()) {
        // TODO: is it good idea to return empty vector instead of optional<vector> or something else?
        return {};
    }

    std::vector<ObjectAndActions> answer;
    if (coordinate.x == 0 && coordinate.y == 0) {
        addPlayer(coordinate, answer);
        addFloor(coordinate, answer);
    } else {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<float> distr(0, 1);

        float probability = distr(eng);
        if (probability < 0.05) {
            addWall(coordinate, answer);
        } else {
            addFloor(coordinate, answer);
            if (probability > 0.99) {
                addArtefact(coordinate, answer);
            }
        }
    }

    generated_coordinates_.insert(coordinate);

    return answer;
}

void OnTheFly::addPlayer(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
    ObjectAndActions player;
    // add Player object
    player.object = std::make_shared<state::object::Player>(state::Identity(generated_identities_++));
    player.object->getCoordinate() = coordinate;
    // add no Player actions
    // ...
    answer.push_back(player);

}

void OnTheFly::addFloor(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
    // add Floor
    ObjectAndActions floor;
    floor.object = std::make_shared<state::object::Floor>(state::Identity(generated_identities_++));
    floor.object->getCoordinate() = coordinate;
    // add no Floor actions
    // ...
    answer.push_back(floor);
}

void OnTheFly::addWall(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
    // add Wall
    ObjectAndActions wall;
    wall.object = std::make_shared<state::object::Wall>(state::Identity(generated_identities_++));
    wall.object->getCoordinate() = coordinate;
    // add no Wall actions
    // ...
    answer.push_back(wall);
}

void OnTheFly::addArtefact(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
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

} // namespace world::generator
