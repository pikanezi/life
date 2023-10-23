//
// Created by Vincent Neel on 18/10/2023.
//

#ifndef LIFE_BUILDING_H
#define LIFE_BUILDING_H

#include <memory>
#include <string>
#include <vector>
#include <json/json.h>

#include "../effects/Effect.h"

class Game;

class Building {
public:
    void built(const Game &game);

    void update(double delta_time, const Game &game);

    static std::unique_ptr<class Building> from_json(const Json::Value& value);

public:
    std::string id;
    std::vector<Effect> build_effects;
    std::vector<Effect> update_effects;
};

#endif //LIFE_BUILDING_H
