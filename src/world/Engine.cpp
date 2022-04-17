#include <iostream>
#include "Engine.h"

#include "generator/OnTheFly.h"
#include "state/action/concrete/PlayerMove.h"

namespace world {

    Engine::Engine() {
        generator_ = std::make_unique<generator::OnTheFly>();
//        // Here I create Player
//        auto playerAndFloor = generator_->generateObjects({0, 0}, state_.getObjectObserver());
//        for (const auto& objectAndActions : playerAndFloor) {
//            state_.getObjectObserver().addObject(objectAndActions.object);
//            for (const auto& action : objectAndActions.actions) {
//                state_.addAction(action);
//            }
//            // TODO: implement adding of actions
//        }
        // Here I create initial place:
        for (int32_t x = -10; x <= 10; ++x) {
            for (int32_t y = -10; y <= 10; ++y) {
                common::Coordinate coordinate = {x, y};
                auto objectsAndActionss = generator_->generateObjects(coordinate, state_.getObjectObserver());
                for (const auto& objectAndActions : objectsAndActionss) {
                    state_.getObjectObserver().addObject(objectAndActions.object);
                    for (const auto& action : objectAndActions.actions) {
                        state_.addAction(action);
                    }
                    // TODO: implement adding of actions
                }
            }
        }
    }

    common::Map Engine::applyCommand(common::Command command) {
        int32_t delta_x;
        int32_t delta_y;
        if (command.inputCommand == common::InputCommand::MOVE_TOP) {
            delta_x = 0; delta_y = -1;
        } else if (command.inputCommand == common::InputCommand::MOVE_LEFT) {
            delta_x = -1; delta_y = 0;
        } else if (command.inputCommand == common::InputCommand::MOVE_BOTTOM) {
            delta_x = 0; delta_y = 1;
        } else if (command.inputCommand == common::InputCommand::MOVE_RIGHT) {
            delta_x = 1; delta_y = 0;
        }
        auto action = std::make_shared<state::action::PlayerMove>(delta_x, delta_y);
        state_.applyAction(action);
        return generateMap();
    }

    common::Map Engine::generateMap() {
        common::Map map;
        auto playerCoordinate = state_.getObjectObserver().getPlayer()->getCoordinate();
        for (int32_t x = playerCoordinate.x - 10; x <= playerCoordinate.x + 10; ++x) {
            for (int32_t y = playerCoordinate.y - 10; y <= playerCoordinate.y + 10; ++y) {
                common::Coordinate currentCoordinate = {x, y};
                map[currentCoordinate] = state_.getObjectObserver().getObjectsTypes(currentCoordinate);
            }
        }
        return map;
    }
}