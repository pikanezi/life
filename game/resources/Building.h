//
// Created by Vincent Neel on 18/10/2023.
//

#ifndef LIFE_BUILDING_H
#define LIFE_BUILDING_H

#include <memory>
#include <string>
#include <vector>
#include <json/json.h>

#include "Cost.h"
#include "../effects/Effect.h"

class GameManager;

class Building {
public:
    void update(double delta_time, GameManager &manager);

    bool can_afford(const GameManager &manager) const;

    static class Building from_json(const Json::Value &value);

public:
    std::string id;

    bool unlocked = false;
    int amount_owned = 0;

    std::vector<Cost> cost;
    std::vector<Effect> active_effects;

    std::vector<Effect> build_effects;
    std::vector<Effect> update_effects;
};

#endif //LIFE_BUILDING_H
