#include "Engine.h"
#include "generator/OnTheFly.h"
#include "state/action/concrete/PlayerInteract.h"
#include "state/action/concrete/PlayerMove.h"
#include <algorithm>
#include <stdexcept>

namespace world {

Engine::Engine() {
    generator_ = std::make_unique<generator::OnTheFly>();
    // Here I create initial place:
    generateWorldAroundPlayer({0, 0});
}

void Engine::applyCommand(const common::ControllerCommand& command) {
    using common::ControllerCommand;

    std::shared_ptr<state::action::AbstractAction> action;
    // TODO: refactor it
    if (command == ControllerCommand::INTERACT) {
        action = std::make_shared<state::action::PlayerInteract>();
    } else {
        int32_t delta_x;
        int32_t delta_y;
        switch (command) {
            case ControllerCommand::IGNORE:
                break;
            case ControllerCommand::MOVE_TOP:
                delta_x = 0;
                delta_y = -1;
                break;
            case ControllerCommand::MOVE_LEFT:
                delta_x = -1;
                delta_y = 0;
                break;
            case ControllerCommand::MOVE_BOTTOM:
                delta_x = 0;
                delta_y = 1;
                break;
            case ControllerCommand::MOVE_RIGHT:
                delta_x = 1;
                delta_y = 0;
                break;
            case ControllerCommand::APPLY_RING:
                // add apply
                break;
            case ControllerCommand::APPLY_STICK:
                // add apply
                break;
            case ControllerCommand::DROP_RING:
                // add drop
                break;
            case ControllerCommand::DROP_STICK:
                // add drop
                break;
            default:
                // throw is better than ignore
                throw std::runtime_error("unknown command sent to engine");
        }
        action = std::make_shared<state::action::PlayerMove>(delta_x, delta_y);
    }

    // TODO: return description string if an external action has false precondition
    state_.applyAction(action);
    // TODO: activate here all internal actions

    generateWorldAroundPlayer(state_.getObjectObserver().getPlayer()->getCoordinate());
}

common::WorldUITransfer Engine::getWorldUITransfer() const {
    common::WorldUITransfer worldUiTransfer;

    {
        common::Map map;
        auto playerCoordinate = state_.getObjectObserver().getPlayer()->getCoordinate();
        int32_t VISIBILITY = 10;
        for (int32_t dx = -VISIBILITY; dx <= VISIBILITY; ++dx) {
            for (int32_t dy = -VISIBILITY; dy <= VISIBILITY; ++dy) {
                common::Coordinate currentCoordinate = {playerCoordinate.x + dx, playerCoordinate.y + dy};
                auto objects = state_.getObjectObserver().getObjectsAtCoordinate(currentCoordinate);
                std::vector<common::ObjectType> objectsTypes(objects.size());
                std::transform(objects.cbegin(), objects.cend(), objectsTypes.begin(), [](const auto& object) {
                    return object->getObjectType();
                });
                map[currentCoordinate] = objectsTypes;
            }
        }
        worldUiTransfer.map = map;
    }
    {
        common::Inventory inventory;
        for (const auto& item : state_.getObjectObserver().getPlayer()->getItems()) {
            common::ItemData itemData;
            itemData.itemType = item->getItemType();
            // TODO: where should we keep description?
            itemData.description = "";
            inventory.push_back(itemData);
        }
        worldUiTransfer.inventory = inventory;
    }
    {
        common::PlayerMetrics playerMetrics;
        auto player = state_.getObjectObserver().getPlayer();
        playerMetrics.hp = std::any_cast<int32_t>(player->getProperty("hp").value());
        playerMetrics.lvl = std::any_cast<int32_t>(player->getProperty("lvl").value());
        playerMetrics.exp = std::any_cast<int32_t>(player->getProperty("exp").value());
        worldUiTransfer.playerMetrics = playerMetrics;
    }
    return worldUiTransfer;
}

void Engine::generateWorldAroundPlayer(common::Coordinate playerCoordinate) {
    int32_t GENSIZE = 10;
    for (int32_t dx = -GENSIZE; dx <= GENSIZE; ++dx) {
        for (int32_t dy = -GENSIZE; dy <= GENSIZE; ++dy) {
            common::Coordinate coordinate = {playerCoordinate.x + dx, playerCoordinate.y + dy};
            auto objectsAndActions = generator_->generateObjects(coordinate, state_.getObjectObserver());
            for (const auto& objectAndActions : objectsAndActions) {
                state_.getObjectObserver().addObject(objectAndActions.object);
                for (const auto& action : objectAndActions.actions) {
                    state_.addAction(action);
                }
                // TODO: implement adding of actions
            }
        }
    }
}

}  // namespace world