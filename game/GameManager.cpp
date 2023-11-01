//
// Created by Vincent Neel on 18/10/2023.
//

#include <fmt/core.h>
#include <memory>

#include "Game.h"
#include "GameManager.h"
#include "effects/Effect.h"
#include "resources/Building.h"
#include "resources/Resource.h"

void GameManager::update(double delta_time) {
    for (auto const &[_, building]: buildings) {
        if (!building->unlocked) {
            continue;
        }
        for (auto const &effect: building->active_effects) {
            execute_duration_effect(effect, delta_time);
        }
    }
}

void GameManager::construct(std::string const &building_id) {
    auto const &building = buildings[building_id];
    if (!building->can_afford(*this)) {
        game.logger.log(fmt::format("GameManager::construct: can't afford building {}", building_id));
        return;
    }

    auto const sender = EffectTarget(Building, building_id);
    for (auto const &c: building->cost) {
        auto const cost_effect = Effect(Consumption, Additive, sender, EffectTarget(Resource, c.resource_id), Instant, -c.amount);
        apply_effect(cost_effect);
    }
    for (auto const &effect: building->build_effects) {
        apply_effect(effect);
    }
    // add a new building
    apply_effect(Effect(Consumption, Additive, sender, EffectTarget(Building, building_id), Instant, 1));
    game.logger.log(fmt::format("building {} constructed", building_id));
}

void GameManager::apply_effect(Effect const &effect) {
    if (!effect.can_activate(*this)) {
        return;
    }
    if (effect.duration != Instant) {
        if (effect.sender.scope == Building) {
            buildings[effect.sender.target]->active_effects.push_back(effect);
        } else {
            active_effects.push_back(effect);
        }
        return;
    }
    execute_instant_effect(effect);
}

void GameManager::execute_instant_effect(Effect const &effect) {
    switch (effect.kind) {
        case Unlock:
            switch (effect.target.scope) {
                case Building:
                    buildings[effect.target.target]->unlocked = true;
                case Resource:
                    resources[effect.target.target]->unlocked = true;
                default:
                    break;
            }
            break;
        case Price:
        case Production:
        case Consumption:
            switch (effect.target.scope) {
                case Resource: {
                    auto const &resource = resources[effect.target.target];
                    if (!resource->unlocked) {
                        game.logger.log(fmt::format("GameManager::execute_instant_effect: resource {} locked", effect.target.target));
                        return;
                    }
                    if (effect.operation == Additive) {
                        *resource += effect.magnitude;
                    } else {
                        *resource *= effect.magnitude;
                    }
                    break;
                }
                case Building: {
                    auto const &building = buildings[effect.target.target];
                    if (!building->unlocked) {
                        game.logger.log(fmt::format("GameManager::execute_instant_effect: building {} locked", effect.target.target));
                        return;
                    }
                    if (effect.operation == Additive) {
                        building->amount_owned += int(effect.magnitude);
                    } else {
                        building->amount_owned *= int(effect.magnitude);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
    }
}

void GameManager::execute_duration_effect(Effect const &effect, double delta_time) {
    switch (effect.kind) {
        case Price:
        case Production:
        case Consumption:
            if (effect.target.scope == Resource) {
                if (effect.operation == Additive) {
                    *resources[effect.target.target] += effect.magnitude * delta_time;
                } else {
                    *resources[effect.target.target] *= effect.magnitude * delta_time;
                }
            }
            break;
        default:
            break;
    }
}

const class Resource *GameManager::resource_by_id(string const &resource_id) const {
    return resources.at(resource_id).get();
}

const class Building *GameManager::building_by_id(std::string const &building_id) const {
    return buildings.at(building_id).get();
}

bool GameManager::is_resource_unlocked(string const &resource_id) const {
    return resources.contains(resource_id);
}

bool GameManager::is_building_unlocked(std::string const &building_id) const {
    return buildings.contains(building_id);
}

void GameManager::load_building(unique_ptr<class Building> building) {
    buildings[building->id] = std::move(building);
}

void GameManager::load_resource(unique_ptr<class Resource> resource) {
    resources[resource->id] = std::move(resource);
}

bool GameManager::is_target_unlocked(EffectTarget const &target) const {
    switch (target.scope) {
        case Resource:
            is_resource_unlocked(target.target);
        case Building:
            is_building_unlocked(target.target);
        default:
            break;
    }
    return false;
}

void GameManager::increment_food() {
    auto const add_food_effect = Effect(Consumption, Additive, EffectTarget::global(), EffectTarget(Resource, "food"), Instant, 1.f);
    apply_effect(add_food_effect);
}