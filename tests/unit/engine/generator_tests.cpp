#include "gtest/gtest.h"

#include "../../../src/world/generator/FromTheDisk.h"
#include "../../../src/world/generator/OnTheFly.h"
#include "../../../src/world/state/State.h"
#include "../../../src/world/state/action/concrete/PlayerMove.h"
#include "../../../src/world/state/action/concrete/PlayerInteract.h"


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
