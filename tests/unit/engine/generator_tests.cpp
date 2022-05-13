#include "gtest/gtest.h"

#include "../../../src/world/generator/FromTheDisk.h"
#include "../../../src/world/generator/OnTheFly.h"
#include "../../../src/world/state/State.h"
#include "../../../src/world/state/action/internal/Move.h"
#include "../../../src/world/state/action/external/PlayerWorldInteract.h"


TEST(generator_tests, stateEqualsItself) {
    world::state::State state;
    world::generator::OnTheFly generator;

    for (int x = -10; x <= 10; ++x) {
        for (int y = -10; y <= 10; ++y) {
            auto answer = generator.generateObjects({x, y}, state.getObjectObserver());

            for (const auto& objectAndAction : answer) {
                state.getObjectObserver().addObject(objectAndAction.object);
                for (const auto& action : objectAndAction.actions) {
                    state.getActionObserver().addAction(action);
                }
            }

        }
    }
    EXPECT_EQ(state, state);
}

TEST(generator_tests, SerializationDeserializationInversibility) {
    world::state::State state;
    world::generator::OnTheFly generator;

    for (int x = -10; x <= 10; ++x) {
        for (int y = -10; y <= 10; ++y) {
            auto answer = generator.generateObjects({x, y}, state.getObjectObserver());

            for (const auto& objectAndAction : answer) {
                state.getObjectObserver().addObject(objectAndAction.object);
                for (const auto& action : objectAndAction.actions) {
                    state.getActionObserver().addAction(action);
                }
            }

        }
    }

    world::generator::serialization::Serializer serializer;
    world::generator::serialization::Deserializer deserializer;

    auto converted_state = deserializer.deserialize(serializer.serialize(state));

    EXPECT_TRUE(state.getObjectObserver() == converted_state.getObjectObserver());
    EXPECT_TRUE(state.getActionObserver() == converted_state.getActionObserver());
}

TEST(generator_tests, PropertiesWithDifferentTypes) {
    world::state::State state;
    world::generator::OnTheFly generator;

    for (int x = -10; x <= 10; ++x) {
        for (int y = -10; y <= 10; ++y) {
            auto answer = generator.generateObjects({x, y}, state.getObjectObserver());

            for (const auto& objectAndAction : answer) {
                state.getObjectObserver().addObject(objectAndAction.object);
                for (const auto& action : objectAndAction.actions) {
                    state.getActionObserver().addAction(action);
                }
            }

        }
    }

    world::generator::serialization::Serializer serializer;
    world::generator::serialization::Deserializer deserializer;

    auto converted_state = deserializer.deserialize(serializer.serialize(state));
    converted_state.getActionObserver().getEveryTurnActions()[0]->setProperty("every_turn", 123);

    EXPECT_TRUE(state.getObjectObserver() == converted_state.getObjectObserver());
    EXPECT_FALSE(state.getActionObserver() == converted_state.getActionObserver());
}

TEST(generator_tests, PropertiesWithDifferentValues) {
    world::state::State state;
    world::generator::OnTheFly generator;

    for (int x = -10; x <= 10; ++x) {
        for (int y = -10; y <= 10; ++y) {
            auto answer = generator.generateObjects({x, y}, state.getObjectObserver());

            for (const auto& objectAndAction : answer) {
                state.getObjectObserver().addObject(objectAndAction.object);
                for (const auto& action : objectAndAction.actions) {
                    state.getActionObserver().addAction(action);
                }
            }

        }
    }

    world::generator::serialization::Serializer serializer;
    world::generator::serialization::Deserializer deserializer;

    auto converted_state = deserializer.deserialize(serializer.serialize(state));
    converted_state.getActionObserver().getEveryTurnActions()[0]->setProperty("every_turn", false);

    EXPECT_TRUE(state.getObjectObserver() == converted_state.getObjectObserver());
    EXPECT_FALSE(state.getActionObserver() == converted_state.getActionObserver());
}