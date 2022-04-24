#include "OnTheFly.h"
#include <algorithm>
#include <random>

namespace world::generator {

std::vector<ObjectAndActions> OnTheFly::generateObjects(common::Coordinate coordinate, const state::object::Observer&) {

    if (std::find(generated_coordinates_.begin(), generated_coordinates_.end(), coordinate) !=
        generated_coordinates_.end()) {
        // TODO: is it good idea to return empty vector instead of optional<vector> or something else?
        return {};
    }

    std::vector<ObjectAndActions> answer;
    if (coordinate.x == 0 && coordinate.y == 0) {
        addPlayer(coordinate, answer, generated_identities_);
        addFloor(coordinate, answer, generated_identities_);
    } else {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<float> distr(0, 1);

        float probability = distr(eng);
        if (probability < 0.05) {
            addWall(coordinate, answer, generated_identities_);
        } else {
            addFloor(coordinate, answer, generated_identities_);
            if (probability > 0.99) {
                addArtefact(coordinate, answer, generated_identities_);
            }
        }
    }

    generated_coordinates_.insert(coordinate);

    return answer;
}

}  // namespace world::generator
