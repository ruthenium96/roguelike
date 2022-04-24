#include "gtest/gtest.h"

#include "../../../src/world/generator/AbstractGenerator.h"
#include "../../../src/world/state/State.h"
#include "../../../src/world/state/action/concrete/PlayerMove.h"
#include "../../../src/world/state/action/concrete/PlayerInteract.h"

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

    state.applyAction(moveActionRight);
    expectedCoordinate.x += 1;
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    state.applyAction(moveActionUp);
    expectedCoordinate.y -= 1;
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    state.applyAction(moveActionUp);
    expectedCoordinate.y -= 1;
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    state.applyAction(moveActionLeft);
    expectedCoordinate.x -= 1;
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    state.applyAction(moveActionDown);
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
    state.applyAction(moveAction);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
    moveAction = std::make_shared<world::state::action::PlayerMove>(-1, 0);
    state.applyAction(moveAction);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
    moveAction = std::make_shared<world::state::action::PlayerMove>(0, 1);
    state.applyAction(moveAction);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
    moveAction = std::make_shared<world::state::action::PlayerMove>(0, -1);
    state.applyAction(moveAction);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
}

TEST(state_tests, interactWithArtefact) {
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

    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 0}).size(), 3);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getItems().size(), 0);
    // TODO: find Action corresponding to Artefact/Item

    auto interactAction = std::make_shared<world::state::action::PlayerInteract>();
    state.applyAction(interactAction);

    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 0}).size(), 2);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getItems().size(), 1);
}