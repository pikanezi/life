//
// Created by Vincent Neel on 18/10/2023.
//

#ifndef LIFE_GAME_MANAGER_H
#define LIFE_GAME_MANAGER_H

#include <json/json.h>
#include <map>
#include <memory>
#include <vector>

#include "resources/Building.h"
#include "resources/Resource.h"

class Game;

using namespace std;

class GameManager {

public:
    explicit GameManager(Game const &game) : game(game) {}

    // Loading
    void load_building(unique_ptr<class Building> building);

    void load_resource(unique_ptr<class Resource> resource);

    // Runtime
    void update(double delta_time);

    void construct(std::string const &building_id);

    void apply_effect(Effect const &effect);

    void increment_food();

    const class Resource *resource_by_id(string const &resource_id) const;

    const class Building *building_by_id(string const &building_id) const;

    bool is_resource_unlocked(string const &resource_id) const;

    bool is_building_unlocked(string const &building_id) const;

    bool is_target_unlocked(EffectTarget const &target) const;

private:
    void execute_effect(Effect const &effect);

private:
    Game const &game;

    vector<class Effect> active_effects;
    map<string, unique_ptr<class Resource>> resources;
    map<string, unique_ptr<class Building>> buildings;
};


#endif//LIFE_GAME_MANAGER_H
