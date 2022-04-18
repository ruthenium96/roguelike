#include <algorithm>
#include "Engine.h"

#include "generator/OnTheFly.h"
#include "state/action/concrete/PlayerMove.h"

namespace world {

    Engine::Engine() {
        generator_ = std::make_unique<generator::OnTheFly>();
        // Here I create initial place:
        generateWorldAroundPlayer({0,0});
    }

    void Engine::applyCommand(const common::ControllerCommand& command) {
        int32_t delta_x;
        int32_t delta_y;
        if (command == common::ControllerCommand::MOVE_TOP) {
            delta_x = 0; delta_y = -1;
        } else if (command == common::ControllerCommand::MOVE_LEFT) {
            delta_x = -1; delta_y = 0;
        } else if (command == common::ControllerCommand::MOVE_BOTTOM) {
            delta_x = 0; delta_y = 1;
        } else if (command == common::ControllerCommand::MOVE_RIGHT) {
            delta_x = 1; delta_y = 0;
        }
        auto action = std::make_shared<state::action::PlayerMove>(delta_x, delta_y);
        state_.applyAction(action);

        generateWorldAroundPlayer(state_.getObjectObserver().getPlayer()->getCoordinate());
    }

    common::Map Engine::getMap() {
        common::Map map;
        auto playerCoordinate = state_.getObjectObserver().getPlayer()->getCoordinate();
        int32_t VISIBILITY = 10;
        for (int32_t dx = -VISIBILITY; dx <= VISIBILITY; ++dx) {
            for (int32_t dy = -VISIBILITY; dy <= VISIBILITY; ++dy) {
                common::Coordinate currentCoordinate = {playerCoordinate.x + dx, playerCoordinate.y + dy};
                auto objects = state_.getObjectObserver().getObjects(currentCoordinate);
                std::vector<common::ObjectType> objectsTypes(objects.size());
                std::transform(objects.cbegin(),
                               objects.cend(),
                               objectsTypes.begin(),
                               [](const auto& object){return object->getObjectType();});
                map[currentCoordinate] = objectsTypes;
            }
        }
        return map;
    }

    void Engine::generateWorldAroundPlayer(common::Coordinate playerCoordinate) {
        int32_t GENSIZE = 10;
        for (int32_t dx = -GENSIZE; dx <= GENSIZE; ++dx) {
            for (int32_t dy = -GENSIZE; dy <= GENSIZE; ++dy) {
                common::Coordinate coordinate = {playerCoordinate.x + dx, playerCoordinate.y + dy};
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
}