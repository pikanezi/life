//
// Created by Vincent Neel on 18/10/2023.
//

#include "Building.h"

void Building::built(const Game &game) {

}

void Building::update(double delta_time, const Game &game) {

}

std::unique_ptr<class Building> Building::from_json(const Json::Value &value) {
    auto building = std::make_unique<Building>();
    building->id = value["id"].asString();

    if (value["build_effects"]) {
        for (const auto &v: value["build_effects"]) {
            building->build_effects.push_back(Effect::from_json(v));
        }
    }
    if (value["update_effects"]) {
        for (const auto &v: value["update_effects"]) {
            building->update_effects.push_back(Effect::from_json(v));
        }
    }
    return building;
}
