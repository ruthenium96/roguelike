#include "OnTheFly.h"
#include "../state/object/concrete/Wall.h"
#include <random>
#include <algorithm>

namespace world::generator {
    std::vector<ObjectAndActions>
    OnTheFly::generateObjects(common::Coordinate coordinate, const state::object::Observer&) {

        if (std::find(generated_coordinates_.begin(), generated_coordinates_.end(), coordinate) != generated_coordinates_.end()) {
            // TODO: is it good idea to return empty vector instead of optional<vector> or something else?
            return {};
        }

        std::vector<ObjectAndActions> answer;
        if (coordinate.x == 0 && coordinate.y == 0) {
            ObjectAndActions player;
            // add Player object
            player.object = std::make_shared<state::object::Player>(state::object::Identity(generated_objects_++));
            player.object->getCoordinate() = coordinate;
            // add no Player actions
            // ...
            answer.push_back(player);
            // add Floor
            ObjectAndActions floor;
            floor.object = std::make_shared<state::object::Floor>(state::object::Identity(generated_objects_++));
            floor.object->getCoordinate() = coordinate;
            // add no Floor objects
            // ...
            answer.push_back(floor);
        } else {
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_real_distribution<float> distr(0, 1);

            float shouldCreateWall = distr(eng);
            if (shouldCreateWall < 0.05) {
                // add Wall
                ObjectAndActions wall;
                wall.object = std::make_shared<state::object::Wall>(state::object::Identity(generated_objects_++));
                wall.object->getCoordinate() = coordinate;
                // add no Wall objects
                // ...
                answer.push_back(wall);
            } else {
                // add Floor
                ObjectAndActions floor;
                floor.object = std::make_shared<state::object::Floor>(state::object::Identity(generated_objects_++));
                floor.object->getCoordinate() = coordinate;
                // add no Floor objects
                // ...
                answer.push_back(floor);
            }
        }

        generated_coordinates_.insert(coordinate);

        return answer;
    }
}