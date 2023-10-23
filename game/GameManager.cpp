//
// Created by Vincent Neel on 18/10/2023.
//

#include <memory>
#include <algorithm>

#include "GameManager.h"

void GameManager::update(double delta_time) {
    for (const auto &[_, resource] : resources) {

    }
}

void GameManager::construct(const std::string &building_id) {
    auto building_pair_it = std::find_if(buildings.begin(), buildings.end(), [building_id](const auto &tuple) {
        const auto &building = std::get<0>(tuple);
        return building->id == building_id;
    });
    if (building_pair_it != buildings.end()) {
        const auto &building = std::get<0>(*building_pair_it);
        building->built(game);
        std::get<1>(*building_pair_it)++;
    } else {
        auto building = make_unique<class Building>();
        buildings.emplace_back(std::move(building), 1);
    }
}

void GameManager::load_building(unique_ptr<class Building> building) {
    tuple<unique_ptr<class Building>, int> pair = {std::move(building), 0};
    buildings.push_back(std::move(pair));
}

const class Resource &GameManager::resource_by_id(const string &resource_id) {
    return *resources[resource_id];
}