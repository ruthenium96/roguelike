#include "GeneratorBuilder.h"
#include "FromTheDisk.h"
#include "OnTheFly.h"
namespace world::generator {

std::unique_ptr<AbstractGenerator> GeneratorBuilder::build() {
    assert(generatorType_.has_value());
    if (generatorType_ == GeneratorType::FROM_THE_DISK) {
        assert(path_.has_value());
        return std::make_unique<FromTheDisk>(path_.value());
    }
    auto onTheFlyPtr = std::make_unique<OnTheFly>();
    if (wallProbability_.has_value()) {
        onTheFlyPtr->wallProbability_ = wallProbability_.value();
    }
    if (objectOnFloorProbability_.has_value()) {
        onTheFlyPtr->objectOnFloorProbability_ = objectOnFloorProbability_.value();
    }
    if (artefactTypeProbability_.has_value()) {
        onTheFlyPtr->artefactTypeProbability_ = artefactTypeProbability_.value();
    }
    if (NPCTypeProbability_.has_value()) {
        onTheFlyPtr->NPCTypeProbability_ = NPCTypeProbability_.value();
    }

    return onTheFlyPtr;
}

GeneratorType& world::generator::GeneratorBuilder::setGeneratorType(world::generator::GeneratorType generatorType) {
    if (generatorType != GeneratorType::FROM_THE_DISK && generatorType != GeneratorType::ON_THE_FLY) {
        assert(0);
    }
    generatorType_ = generatorType;
    assert(checkConsistence());
    return reinterpret_cast<GeneratorType&>(*this);
}

GeneratorType& GeneratorBuilder::setPath(std::filesystem::path path) {
    path_ = path;
    assert(checkConsistence());
    return reinterpret_cast<GeneratorType&>(*this);
}

GeneratorType& GeneratorBuilder::setWallProbability(std::array<float, 1> wallProbability) {
    wallProbability_ = wallProbability;
    assert(checkConsistence());
    return reinterpret_cast<GeneratorType&>(*this);
}

GeneratorType& GeneratorBuilder::setObjectOnFloorProbability(std::array<float, 3> objectOnFloorProbability) {
    objectOnFloorProbability_ = objectOnFloorProbability;
    assert(checkConsistence());
    return reinterpret_cast<GeneratorType&>(*this);
}

GeneratorType& GeneratorBuilder::setNPCTypeProbability(std::array<float, 2> NPCTypeProbability) {
    NPCTypeProbability_ = NPCTypeProbability;
    assert(checkConsistence());
    return reinterpret_cast<GeneratorType&>(*this);
}

GeneratorType& GeneratorBuilder::setArtefactTypeProbability(std::array<float, 1> artefactTypeProbability) {
    artefactTypeProbability_ = artefactTypeProbability;
    assert(checkConsistence());
    return reinterpret_cast<GeneratorType&>(*this);
}

bool GeneratorBuilder::checkConsistence() {
    bool any_of_disk =
        (path_.has_value() || (generatorType_.has_value() && generatorType_.value() == GeneratorType::FROM_THE_DISK));
    bool any_of_probabilities = (wallProbability_.has_value() || objectOnFloorProbability_.has_value() ||
                                 NPCTypeProbability_.has_value() || artefactTypeProbability_.has_value());
    return (any_of_disk ^ any_of_probabilities);
}

}  // namespace world::generator