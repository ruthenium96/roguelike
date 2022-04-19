#include "OnTheFly.h"
#include "../state/object/concrete/Wall.h"
#include "../state/object/concrete/Artefact.h"
#include "../state/item/concrete/Stick.h"
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

        float shouldCreateWall = distr(eng);
        if (shouldCreateWall < 0.05) {
            addWall(coordinate, answer);
        } else {
            addFloor(coordinate, answer);
        }
    }

    generated_coordinates_.insert(coordinate);

    return answer;
}

void OnTheFly::addPlayer(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
    ObjectAndActions player;
    // add Player object
    player.object = std::make_shared<state::object::Player>(state::object::Identity(generated_objects_++));
    player.object->getCoordinate() = coordinate;
    // add no Player actions
    // ...
    answer.push_back(player);

}

void OnTheFly::addFloor(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
    // add Floor
    ObjectAndActions floor;
    floor.object = std::make_shared<state::object::Floor>(state::object::Identity(generated_objects_++));
    floor.object->getCoordinate() = coordinate;
    // add no Floor actions
    // ...
    answer.push_back(floor);
}

void OnTheFly::addWall(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
    // add Wall
    ObjectAndActions wall;
    wall.object = std::make_shared<state::object::Wall>(state::object::Identity(generated_objects_++));
    wall.object->getCoordinate() = coordinate;
    // add no Wall actions
    // ...
    answer.push_back(wall);
}

void OnTheFly::addArtefact(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
    // add Artefact
    ObjectAndActions artefact;
    artefact.object = std::make_shared<state::object::Artefact>(state::object::Identity(generated_objects_++));
    artefact.object->getCoordinate() = coordinate;
    // add Artefact item
    artefact.object->getItems().push_back(std::make_unique<world::state::item::Stick>());
    // add Artefact actions
    // artefact.actions.push_back();
    answer.push_back(artefact);


}

} // namespace world::generator
