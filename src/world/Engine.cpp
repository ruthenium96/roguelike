#include <iostream>
#include "Engine.h"

#include "generator/OnTheFly.h"
#include "state/action/concrete/PlayerMove.h"

namespace world {

    Engine::Engine() {
        generator_ = std::make_unique<generator::OnTheFly>();
        // Here I create Player
        auto playerAndFloor = generator_->generateObjects({0, 0}, state_.getObjectObserver());
        for (const auto& objectAndActions : playerAndFloor) {
            state_.getObjectObserver().addObject(objectAndActions.object);
            for (const auto& action : objectAndActions.actions) {
                state_.addAction(action);
            }
            // TODO: implement adding of actions
        }
    }

    void Engine::start() {
        while (true) {
            char azaza;
            std::cin >> azaza;
            if (azaza == 'Q') {
                break;
            } else if (azaza == 'W' || azaza == 'A' || azaza == 'S' || azaza == 'D') {
                int32_t delta_x;
                int32_t delta_y;
                if (azaza == 'W') {
                    delta_x = 0; delta_y = 1;
                } else if (azaza == 'A') {
                    delta_x = -1; delta_y = 0;
                } else if (azaza == 'S') {
                    delta_x = 0; delta_y = -1;
                } else if (azaza == 'D') {
                    delta_x = 1; delta_y = 0;
                }

                auto action = std::make_shared<state::action::PlayerMove>(delta_x, delta_y);
                state_.applyAction(action);
            }
            std::cout << state_.getObjectObserver().getPlayer()->getCoordinate().x << " " <<
                      state_.getObjectObserver().getPlayer()->getCoordinate().y << std::endl;
        }
    }
}