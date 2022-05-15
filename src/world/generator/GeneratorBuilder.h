#ifndef ARCH_ROGUELIKE_GENERATORBUILDER_H
#define ARCH_ROGUELIKE_GENERATORBUILDER_H

#include "AbstractGenerator.h"

namespace world::generator {

enum class GeneratorType { FROM_THE_DISK, ON_THE_FLY };
// Builder for Generator class
class GeneratorBuilder {
    std::unique_ptr<AbstractGenerator> build();

    GeneratorType& setGeneratorType(GeneratorType generatorType);
    GeneratorType& setPath(std::filesystem::path path);
    // wall will be created if randomNumber < wallProbability_[0]
    GeneratorType& setWallProbability(std::array<float, 1> wallProbability);
    // Artefact, NPC, Mold probabilities
    GeneratorType& setObjectOnFloorProbability(std::array<float, 3> objectOnFloorProbability);
    // Stick, the rest is Ring
    GeneratorType& setArtefactTypeProbability(std::array<float, 1> artefactTypeProbability);
    // Aggressive, Coward, the rest is Inactive
    GeneratorType& setNPCTypeProbability(std::array<float, 2> NPCTypeProbability);

  private:
    bool checkConsistence();
    std::optional<GeneratorType> generatorType_;
    std::optional<std::filesystem::path> path_;
    std::optional<std::array<float, 1>> wallProbability_;
    std::optional<std::array<float, 3>> objectOnFloorProbability_;
    std::optional<std::array<float, 2>> NPCTypeProbability_;
    std::optional<std::array<float, 1>> artefactTypeProbability_;
};
}  // namespace world::generator

#endif  // ARCH_ROGUELIKE_GENERATORBUILDER_H
