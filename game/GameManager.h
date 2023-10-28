//
// Created by Vincent Neel on 18/10/2023.
//

#ifndef LIFE_GAME_MANAGER_H
#define LIFE_GAME_MANAGER_H

#include <map>
#include <memory>
#include <vector>
#include <json/json.h>

#include "resources/Resource.h"
#include "resources/Building.h"

class Game;

using namespace std;

class GameManager {

public:
    explicit GameManager(const Game &game) : game(game) {}

    // Loading
    void load_building(unique_ptr<class Building> building);

    void load_resource(unique_ptr<class Resource> resource);

    // Runtime
    void update(double delta_time);

    void construct(const std::string &building_id);

    void apply_effect(const Effect &effect);

    void increment_food();
    
    const class Resource *resource_by_id(const string &resource_id) const;

    const class Building *building_by_id(const string &building_id) const;

    bool is_resource_unlocked(const string &resource_id) const;

    bool is_building_unlocked(const string &building_id) const;

    bool is_target_unlocked(const EffectTarget &target) const;

private:
    void execute_effect(const Effect &effect);

private:
    const Game &game;

    vector<class Effect> active_effects;
    map<string, unique_ptr<class Resource>> resources;
    map<string, unique_ptr<class Building>> buildings;
};


#endif //LIFE_GAME_MANAGER_H
