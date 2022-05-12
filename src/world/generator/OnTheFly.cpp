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
        addPlayer(coordinate, answer, generated_identities_);
        addFloor(coordinate, answer, generated_identities_);
    } else {

        float probability = distribution_(randomEngine_);
        if (probability < 0.05) {
            addWall(coordinate, answer, generated_identities_);
        } else {
            addFloor(coordinate, answer, generated_identities_);
            if (probability > 0.99) {
                addArtefact(coordinate, answer, generated_identities_);
            } else if (probability > 0.985) {
                addNPC(coordinate, answer, generated_identities_);
            }
        }
    }

    generated_coordinates_.insert(coordinate);

    return answer;
}

OnTheFly::OnTheFly() {
    std::random_device rd;
    randomEngine_ = std::default_random_engine (rd());
    distribution_ = std::uniform_real_distribution<float>(0, 1);
}

}  // namespace world::generator
