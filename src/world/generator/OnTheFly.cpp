#include "OnTheFly.h"

namespace world::generator {
    std::vector<ObjectAndActions>
    OnTheFly::generateObjects(state::object::Coordinate coordinate, const state::object::Observer&) {

        std::vector<ObjectAndActions> answer;
        if (coordinate.x == 0 && coordinate.y == 0) {
            ObjectAndActions player;
            // add Player object
            player.object = std::make_shared<state::object::Player>(state::object::Identity(generated_objects_++));
            // add no Player actions
            // ...
            answer.push_back(player);
        }
        // add Floor
        ObjectAndActions floor;
        floor.object = std::make_shared<state::object::Floor>(state::object::Identity(generated_objects_++));
        // add no Floor objects
        // ...
        answer.push_back(floor);

        return answer;
    }
}