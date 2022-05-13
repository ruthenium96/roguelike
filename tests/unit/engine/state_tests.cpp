#include "gtest/gtest.h"

#include "../../../src/world/generator/AbstractGenerator.h"
#include "../../../src/world/state/State.h"
#include "../../../src/world/state/action/external/PlayerDrop.h"
#include "../../../src/world/state/action/external/PlayerWorldInteract.h"
#include "../../../src/world/state/action/internal/Move.h"
#include "../../../src/world/state/action/external/PlayerUIInteract.h"

namespace world::generator {
class GeneratorForTests : public AbstractGenerator {
public:
    void addPlayerPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
        addPlayer(coordinate, answer);
    };
    void addFloorPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
        addFloor(coordinate, answer);
    };
    void addWallPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
        addWall(coordinate, answer);
    };
    void addArtefactPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
        addArtefact(coordinate, answer);
    };
    void addAggresiveNPCPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
        addNPC(coordinate, answer, {0.0, 0.0});
    }
    void addCowardNPCPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
        addNPC(coordinate, answer, {1.0, 0.0});
    }
    void addInactiveNPCPublic(common::Coordinate coordinate, std::vector<ObjectAndActions>& answer) {
        addNPC(coordinate, answer, {1.0, 1.0});
    }
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
    // .......
    // .......
    // .......
    // ...P...
    // .......
    // .......
    // .......
    generator.addPlayerPublic({0, 0}, answer);
    for (int x = -2; x <= 2; ++x) {
        for (int y = -2; y <= 2; ++y) {
            generator.addFloorPublic({x, y}, answer);
        }
    }

    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }
    common::Coordinate expectedCoordinate = {0, 0};
    auto playerIdentity = state.getObjectObserver().getPlayer()->getIdentity();
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    auto moveActionRight = std::make_shared<world::state::action::Move>(playerIdentity, 1, 0);
    auto moveActionLeft = std::make_shared<world::state::action::Move>(playerIdentity, -1, 0);
    auto moveActionUp = std::make_shared<world::state::action::Move>(playerIdentity, 0, -1);
    auto moveActionDown = std::make_shared<world::state::action::Move>(playerIdentity, 0, 1);

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
    //  #
    // #P#
    //  #
    generator.addPlayerPublic({0, 0}, answer);
    generator.addFloorPublic({0, 0}, answer);
    generator.addWallPublic({0, 1}, answer);
    generator.addWallPublic({0, -1}, answer);
    generator.addWallPublic({1, 0}, answer);
    generator.addWallPublic({-1, 0}, answer);

    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }
    common::Coordinate expectedCoordinate = {0, 0};
    auto playerIdentity = state.getObjectObserver().getPlayer()->getIdentity();
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);

    auto moveAction = std::make_shared<world::state::action::Move>(playerIdentity, 1, 0);
    ASSERT_EQ(state.applyAction(moveAction), false);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
    moveAction = std::make_shared<world::state::action::Move>(playerIdentity, -1, 0);
    ASSERT_EQ(state.applyAction(moveAction), false);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
    moveAction = std::make_shared<world::state::action::Move>(playerIdentity, 0, 1);
    ASSERT_EQ(state.applyAction(moveAction), false);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
    moveAction = std::make_shared<world::state::action::Move>(playerIdentity, 0, -1);
    ASSERT_EQ(state.applyAction(moveAction), false);
    ASSERT_EQ(state.getObjectObserver().getPlayer()->getCoordinate(), expectedCoordinate);
}

TEST(state_tests, interactWithArtefactAndDropItem) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    generator.addPlayerPublic({0, 0}, answer);
    generator.addFloorPublic({0, 0}, answer);
    generator.addArtefactPublic({0, 0}, answer);

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
    generator.addPlayerPublic({0, 0}, answer);
    generator.addFloorPublic({0, 0}, answer);

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
    generator.addPlayerPublic({0, 0}, answer);
    generator.addFloorPublic({0, 0}, answer);
    generator.addArtefactPublic({0, 0}, answer);


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
    generator.addPlayerPublic({0, 0}, answer);
    generator.addFloorPublic({0, 0}, answer);
    generator.addArtefactPublic({0, 0}, answer);


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
    generator.addPlayerPublic({0, 0}, answer);
    generator.addFloorPublic({0, 0}, answer);
    generator.addArtefactPublic({0, 0}, answer);


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

TEST(state_tests, aggressiveNPC) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    generator.addPlayerPublic({0, 0}, answer);
    generator.addFloorPublic({0, 0}, answer);
    generator.addFloorPublic({0, 1}, answer);
    generator.addAggresiveNPCPublic({0, 1}, answer);

    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }

    auto player = state.getObjectObserver().getPlayer();
    std::shared_ptr<world::state::object::AbstractObject> enemy = nullptr;
    for (const auto& object : state.getObjectObserver().getObjectsAtCoordinate({0, 1})) {
        if (object->getObjectType() == common::ObjectType::NPC) {
            enemy = object;
        }
    }
    assert(enemy != nullptr);
    auto old_hp_enemy = std::any_cast<int32_t>(enemy->getProperty("hp").value());
    auto old_hp_player = std::any_cast<int32_t>(player->getProperty("hp").value());

    auto playerAttackAction = std::make_shared<world::state::action::Move>(player->getIdentity(), 0, 1);
    ASSERT_EQ(state.applyAction(playerAttackAction), true);
    auto new_hp_enemy = std::any_cast<int32_t>(enemy->getProperty("hp").value());
    ASSERT_TRUE(new_hp_enemy < old_hp_enemy);
    state.applyEveryTurnInternalActions();
    auto new_hp_player = std::any_cast<int32_t>(player->getProperty("hp").value());
    ASSERT_TRUE(new_hp_player < old_hp_player);
    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 0}).size(), 2);
    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 1}).size(), 2);
}

TEST(state_tests, twoAggressiveNPC) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    generator.addPlayerPublic({0, 0}, answer);
    generator.addFloorPublic({0, 0}, answer);
    generator.addFloorPublic({0, 1}, answer);
    generator.addAggresiveNPCPublic({0, 1}, answer);
    generator.addFloorPublic({0, 2}, answer);
    generator.addAggresiveNPCPublic({0, 2}, answer);


    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }

    auto player = state.getObjectObserver().getPlayer();
    std::shared_ptr<world::state::object::AbstractObject> enemy_close = nullptr;
    for (const auto& object : state.getObjectObserver().getObjectsAtCoordinate({0, 1})) {
        if (object->getObjectType() == common::ObjectType::NPC) {
            enemy_close = object;
        }
    }
    std::shared_ptr<world::state::object::AbstractObject> enemy_far = nullptr;
    for (const auto& object : state.getObjectObserver().getObjectsAtCoordinate({0, 2})) {
        if (object->getObjectType() == common::ObjectType::NPC) {
            enemy_far = object;
        }
    }

    assert(enemy_close != nullptr && enemy_far != nullptr);
    auto old_hp_enemy_close = std::any_cast<int32_t>(enemy_close->getProperty("hp").value());
    auto old_hp_enemy_far = std::any_cast<int32_t>(enemy_close->getProperty("hp").value());
    auto old_hp_player = std::any_cast<int32_t>(player->getProperty("hp").value());

    auto playerAttackAction = std::make_shared<world::state::action::Move>(player->getIdentity(), 0, 1);
    ASSERT_EQ(state.applyAction(playerAttackAction), true);
    auto new_hp_enemy_close = std::any_cast<int32_t>(enemy_close->getProperty("hp").value());
    auto new_hp_enemy_far = std::any_cast<int32_t>(enemy_far->getProperty("hp").value());
    ASSERT_TRUE(new_hp_enemy_close < old_hp_enemy_close);
    ASSERT_EQ(new_hp_enemy_far, old_hp_enemy_far);
    state.applyEveryTurnInternalActions();
    auto new_hp_player = std::any_cast<int32_t>(player->getProperty("hp").value());
    new_hp_enemy_far = std::any_cast<int32_t>(enemy_far->getProperty("hp").value());
    ASSERT_TRUE(new_hp_player < old_hp_player);
    ASSERT_EQ(new_hp_enemy_far, old_hp_enemy_far);

    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 0}).size(), 2);
    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 1}).size(), 2);
    ASSERT_EQ(state.getObjectObserver().getObjectsAtCoordinate({0, 2}).size(), 2);
}

TEST(state_tests, cowardNPC) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    generator.addPlayerPublic({0, 0}, answer);
    generator.addCowardNPCPublic({0, 1}, answer);

    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }

    auto player = state.getObjectObserver().getPlayer();
    std::shared_ptr<world::state::object::AbstractObject> enemy = nullptr;
    for (const auto& object : state.getObjectObserver().getObjectsAtCoordinate({0, 1})) {
        if (object->getObjectType() == common::ObjectType::NPC) {
            enemy = object;
        }
    }
    assert(enemy != nullptr);
    common::Coordinate wantedCoordinate = {0, 1};
    ASSERT_EQ(enemy->getCoordinate(), wantedCoordinate);

    state.applyEveryTurnInternalActions();
    ASSERT_NE(enemy->getCoordinate(), wantedCoordinate);
}

TEST(state_tests, inactiveNPC) {
    world::state::State state;
    world::generator::GeneratorForTests generator;

    std::vector<world::generator::ObjectAndActions> answer;
    generator.addPlayerPublic({0, 0}, answer);
    generator.addInactiveNPCPublic({0, 1}, answer);

    for (const auto& objectAndAction : answer) {
        state.getObjectObserver().addObject(objectAndAction.object);
        for (const auto& action : objectAndAction.actions) {
            state.getActionObserver().addAction(action);
        }
    }

    auto player = state.getObjectObserver().getPlayer();
    std::shared_ptr<world::state::object::AbstractObject> enemy = nullptr;
    for (const auto& object : state.getObjectObserver().getObjectsAtCoordinate({0, 1})) {
        if (object->getObjectType() == common::ObjectType::NPC) {
            enemy = object;
        }
    }
    assert(enemy != nullptr);
    common::Coordinate wantedCoordinate = {0, 1};
    ASSERT_EQ(enemy->getCoordinate(), wantedCoordinate);

    state.applyEveryTurnInternalActions();
    ASSERT_EQ(enemy->getCoordinate(), wantedCoordinate);
}