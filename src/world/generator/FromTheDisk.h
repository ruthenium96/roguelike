#ifndef ARCH_ROGUELIKE_FROMTHEDISK_H
#define ARCH_ROGUELIKE_FROMTHEDISK_H

#include "AbstractGenerator.h"
#include "serialization/Deserializer.h"

namespace world::generator {

class FromTheDisk : public AbstractGenerator {
public:

    explicit FromTheDisk(std::filesystem::path path);

    std::vector<ObjectAndActions>
    generateObjects(common::Coordinate coordinate, const state::object::Observer &observer) override;
    // returns reference to deserializer
    const serialization::Deserializer& getLoader() const;

private:
    serialization::Deserializer loader_;
    std::optional<world::state::State> loadedState_;
    std::filesystem::path path_;
    bool wasLoaded_ = false;
    std::set<common::Coordinate> generated_coordinates_;
    std::set<common::Coordinate> loaded_coordinates_;

};
}

#endif //ARCH_ROGUELIKE_FROMTHEDISK_H
