//
// Created by Vincent Neel on 18/10/2023.
//

#ifndef LIFE_BUILDING_H
#define LIFE_BUILDING_H

#include <json/json.h>
#include <memory>
#include <string>
#include <vector>

#include "../effects/Effect.h"
#include "Cost.h"

class GameManager;

class Building {
public:
    bool can_afford(GameManager const &manager) const;

    static class Building from_json(Json::Value const &value);

public:
    std::string id;

    bool unlocked = false;
    int amount_owned = 0;

    std::vector<Cost> cost;
    std::vector<Effect> active_effects;

    std::vector<Effect> build_effects;
    std::vector<Effect> update_effects;
};

#endif//LIFE_BUILDING_H
