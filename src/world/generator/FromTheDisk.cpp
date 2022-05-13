#include "FromTheDisk.h"

#include <utility>

namespace world::generator {
std::vector<ObjectAndActions> FromTheDisk::generateObjects(common::Coordinate coordinate, const state::object::Observer &observer) {
    if (std::find(generated_coordinates_.begin(), generated_coordinates_.end(), coordinate) !=
    generated_coordinates_.end()) {
        return {};
    }

    std::vector<ObjectAndActions> answer;
    if (loadedState_.has_value() && std::find(loaded_coordinates_.begin(), loaded_coordinates_.end(), coordinate) != generated_coordinates_.end()) {
        for (const auto& object : loadedState_.value().getObjectObserver().getAllObjects()) {
            ObjectAndActions only_object;
            only_object.object = object;
            answer.push_back(only_object);
        }
        ObjectAndActions only_actions;
        for (const auto& action : loadedState_.value().getActionObserver().getAllActions()) {
            only_actions.actions.push_back(action);
        }
        answer.push_back(only_actions);

        // free memory
        loadedState_ = std::nullopt;
        generated_coordinates_.insert(loaded_coordinates_.begin(), loaded_coordinates_.end());
        loaded_coordinates_.clear();
    } else {
        // Generate Walls outside loaded Map
        addWall(coordinate, answer);
    }
    return answer;
}

const serialization::Deserializer &FromTheDisk::getLoader() const {
    return loader_;
}

FromTheDisk::FromTheDisk(std::filesystem::path path) : path_(std::move(path)) {
    loadedState_ = loader_.deserialize_from_file(path_);
    uint64_t generated_identity_max = 0;
    for (const auto& object : loadedState_.value().getObjectObserver().getAllObjects()) {
        auto coordinate = object->getCoordinate();
        if (std::find(loaded_coordinates_.begin(), loaded_coordinates_.end(), coordinate) == generated_coordinates_.end()) {
            loaded_coordinates_.insert(coordinate);
        }
        auto identity_as_number = object->getIdentity().asNumber();
        generated_identity_max = std::max(generated_identity_max, identity_as_number);
    }
    state::IdentityGenerator::setTo(generated_identity_max);
}

}