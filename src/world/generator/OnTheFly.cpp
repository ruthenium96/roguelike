#include "OnTheFly.h"
#include <algorithm>

namespace world::generator {

std::vector<ObjectAndActions> OnTheFly::generateObjects(common::Coordinate coordinate, const state::object::Observer&) {

    if (std::find(generated_coordinates_.begin(), generated_coordinates_.end(), coordinate) !=
        generated_coordinates_.end()) {
        return {};
    }

    std::vector<ObjectAndActions> answer;
    if (coordinate.x == 0 && coordinate.y == 0) {
        addPlayer(coordinate, answer);
        addFloor(coordinate, answer);
    } else {

        float probability = distribution_(randomEngine_);
        if (probability < 0.05) {
            addWall(coordinate, answer);
        } else {
            addFloor(coordinate, answer);
            if (probability > 0.99) {
                addArtefact(coordinate, answer);
            } else if (probability > 0.985) {
                addNPC(coordinate, answer);
            }
        }
    }

    generated_coordinates_.insert(coordinate);

    return answer;
}

}  // namespace world::generator
