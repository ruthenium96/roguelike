#include "gtest/gtest.h"

#include "../../../src/world/generator/AbstractGenerator.h"
#include "../../../src/world/state/State.h"
#include "../../../src/world/state/action/external/PlayerDrop.h"
#include "../../../src/world/state/action/external/PlayerWorldInteract.h"
#include "../../../src/world/state/action/external/PlayerMove.h"
#include "../../../src/world/state/action/external/PlayerUIInteract.h"

namespace world::generator {
class GeneratorForTests : public AbstractGenerator {
public:
    void addPlayerPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer, uint64_t& generated_identities_) {
        addPlayer(coordinate, answer, generated_identities_);
    };
    void addFloorPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer, uint64_t& generated_identities_) {
        addFloor(coordinate, answer, generated_identities_);
    };
    void addWallPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer, uint64_t& generated_identities_) {
        addWall(coordinate, answer, generated_identities_);
    };
    void addArtefactPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer, uint64_t& generated_identities_) {
        addArtefact(coordinate, answer, generated_identities_);
    };
    std::vector<ObjectAndActions> generateObjects(common::Coordinate coordinate,
                                                  const state::object::Observer &observer) override {
        return {};
    }
};
}

TEST(state_tests, canWalkOntoFloor) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    uint64_t generated_identities;
    // .......
    // .......
    // .......
    // ...P...
    // .......
    // .......
    // .......
    generator.addPlayerPublic({0, 0}, answer, generated_identities);
    for (int x = -2; x <= 2; ++x) {
        for (int y = -2; y <= 2; ++y) {
            generator.addFloorPublic({x, y}, answer, generated_identities);
        }
    }

    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }
    common::Coordinate expectedCoordinate = {0, 0};
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    auto moveActionRight = std::make_shared<world::state::action::PlayerMove>(1, 0);
    auto moveActionLeft = std::make_shared<world::state::action::PlayerMove>(-1, 0);
    auto moveActionUp = std::make_shared<world::state::action::PlayerMove>(0, -1);
    auto moveActionDown = std::make_shared<world::state::action::PlayerMove>(0, 1);

    ASSERT_EQ(state.applyAction(moveActionRight), true);
    expectedCoordinate.x += 1;
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    ASSERT_EQ(state.applyAction(moveActionUp), true);
    expectedCoordinate.y -= 1;
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    ASSERT_EQ(state.applyAction(moveActionUp), true);
    expectedCoordinate.y -= 1;
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    ASSERT_EQ(state.applyAction(moveActionLeft), true);
    expectedCoordinate.x -= 1;
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    ASSERT_EQ(state.applyAction(moveActionDown), true);
    expectedCoordinate.y += 1;
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
}

TEST(state_tests, cannotWalkIntoWall) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    uint64_t generated_identities;
    //  #
    // #P#
    //  #
    generator.addPlayerPublic({0, 0}, answer, generated_identities);
    generator.addFloorPublic({0, 0}, answer, generated_identities);
    generator.addWallPublic({0, 1}, answer, generated_identities);
    generator.addWallPublic({0, -1}, answer, generated_identities);
    generator.addWallPublic({1, 0}, answer, generated_identities);
    generator.addWallPublic({-1, 0}, answer, generated_identities);

    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }
    common::Coordinate expectedCoordinate = {0, 0};
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    auto moveAction = std::make_shared<world::state::action::PlayerMove>(1, 0);
    ASSERT_EQ(state.applyAction(moveAction), false);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
    moveAction = std::make_shared<world::state::action::PlayerMove>(-1, 0);
    ASSERT_EQ(state.applyAction(moveAction), false);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
    moveAction = std::make_shared<world::state::action::PlayerMove>(0, 1);
    ASSERT_EQ(state.applyAction(moveAction), false);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
    moveAction = std::make_shared<world::state::action::PlayerMove>(0, -1);
    ASSERT_EQ(state.applyAction(moveAction), false);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
}

TEST(state_tests, interactWithArtefactAndDropItem) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    uint64_t generated_identities;
    generator.addPlayerPublic({0, 0}, answer, generated_identities);
    generator.addFloorPublic({0, 0}, answer, generated_identities);
    generator.addArtefactPublic({0, 0}, answer, generated_identities);

    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }

    for (int _ = 0; _ < 10; ++_) {
        ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 0}).size(), 3);
        ASSERT_EQ(state.getObjectObserver().getPlayer()->getItems().size(), 0);

        auto interactAction = std::make_shared<world::state::action::PlayerWorldInteract>();
        ASSERT_EQ(state.applyAction(interactAction), true);

        ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 0}).size(), 2);
        ASSERT_EQ(state.getObjectObserver().getPlayer()->getItems().size(), 1);

        auto itemType = state.getObjectObserver().getPlayer()->getItems()[0]->getItemType();
        auto dropAction = std::make_shared<world::state::action::PlayerDrop>(itemType);
        ASSERT_EQ(state.applyAction(dropAction), true);
    }

    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 0}).size(), 3);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getItems().size(), 0);
}

TEST(state_tests, interactWithNothing) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    uint64_t generated_identities;
    generator.addPlayerPublic({0, 0}, answer, generated_identities);
    generator.addFloorPublic({0, 0}, answer, generated_identities);

    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }

    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 0}).size(), 2);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getItems().size(), 0);
    // TODO: find Action corresponding to Artefact/Item

    auto interactAction = std::make_shared<world::state::action::PlayerWorldInteract>();
    ASSERT_EQ(state.applyAction(interactAction), false);

    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 0}).size(), 2);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getItems().size(), 0);
}

TEST(state_tests, wearUnwearItem) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    uint64_t generated_identities;
    generator.addPlayerPublic({0, 0}, answer, generated_identities);
    generator.addFloorPublic({0, 0}, answer, generated_identities);
    generator.addArtefactPublic({0, 0}, answer, ++generated_identities);


    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }

    auto interactAction = std::make_shared<world::state::action::PlayerWorldInteract>();
    ASSERT_EQ(state.applyAction(interactAction), true);

    auto itemType = state.getObjectObserver().getPlayer()->getItems().back()->getItemType();

    for (int _ = 0; _ < 10; ++_) {
        auto wearUnwearAction = std::make_shared<world::state::action::PlayerUIInteract>(itemType, common::LEFTHAND);
        ASSERT_EQ(state.applyAction(wearUnwearAction), true);
        ASSERT_TRUE(state.getObjectObserver().getPlayer()->getProperty("leftHand").has_value());

        ASSERT_EQ(state.applyAction(wearUnwearAction), true);
        ASSERT_FALSE(state.getObjectObserver().getPlayer()->getProperty("leftHand").has_value());
    }
}

TEST(state_tests, cannotWearTwice) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    uint64_t generated_identities;
    generator.addPlayerPublic({0, 0}, answer, generated_identities);
    generator.addFloorPublic({0, 0}, answer, generated_identities);
    generator.addArtefactPublic({0, 0}, answer, ++generated_identities);


    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }

    auto interactAction = std::make_shared<world::state::action::PlayerWorldInteract>();
    ASSERT_EQ(state.applyAction(interactAction), true);

    auto itemType = state.getObjectObserver().getPlayer()->getItems().back()->getItemType();
    auto wearAction = std::make_shared<world::state::action::PlayerUIInteract>(itemType, common::LEFTHAND);
    ASSERT_EQ(state.applyAction(wearAction), true);

    auto wearAction_two = std::make_shared<world::state::action::PlayerUIInteract>(itemType, common::RIGHTHAND);
    ASSERT_EQ(state.applyAction(wearAction_two), false);
}

TEST(state_tests, cannotDropWhileWeared) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    uint64_t generated_identities;
    generator.addPlayerPublic({0, 0}, answer, generated_identities);
    generator.addFloorPublic({0, 0}, answer, generated_identities);
    generator.addArtefactPublic({0, 0}, answer, ++generated_identities);


    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }

    auto interactAction = std::make_shared<world::state::action::PlayerWorldInteract>();
    ASSERT_EQ(state.applyAction(interactAction), true);

    auto itemType = state.getObjectObserver().getPlayer()->getItems().back()->getItemType();
    auto wearAction = std::make_shared<world::state::action::PlayerUIInteract>(itemType, common::LEFTHAND);
    ASSERT_EQ(state.applyAction(wearAction), true);

    auto dropAction = std::make_shared<world::state::action::PlayerDrop>(itemType);
    ASSERT_EQ(state.applyAction(dropAction), false);
}