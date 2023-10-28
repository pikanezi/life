//
// Created by Vincent Neel on 18/10/2023.
//

#include <algorithm>

#include "Building.h"
#include "../GameManager.h"

void Building::update(double delta_time, GameManager &manager) {

}

bool Building::can_afford(const GameManager &manager) const {
    return std::all_of(cost.cbegin(), cost.cend(),
                       [&](const Cost &c) {
                           return manager.resource_by_id(c.resource_id)->amount >= c.amount;
                       });
}

class Building Building::from_json(const Json::Value &value) {
    Building building;
    building.id = value["id"].asString();
    building.unlocked = value["unlocked"] && value["unlocked"].asBool();

    if (value["cost"]) {
        for (const auto &v: value["cost"]) {
            building.cost.push_back(Cost::from_json(v));
        }
    }
    if (value["build_effects"]) {
        for (const auto &v: value["buildEffects"]) {
            building.build_effects.push_back(Effect::from_json(v));
        }
    }
    if (value["update_effects"]) {
        for (const auto &v: value["update_effects"]) {
            building.update_effects.push_back(Effect::from_json(v));
        }
    }
    return building;
}
