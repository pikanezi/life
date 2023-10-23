//
// Created by Vincent Neel on 18/10/2023.
//

#ifndef LIFE_GAME_MANAGER_H
#define LIFE_GAME_MANAGER_H

#include <map>
#include <tuple>
#include <vector>
#include <memory>
#include <json/json.h>

#include "resources/Resource.h"
#include "resources/Building.h"

class Game;

using namespace std;

class GameManager {

public:
    explicit GameManager(const Game &game) : game(game) {}

    void update(double delta_time);

    void construct(const std::string &building_id);

    void load_building(unique_ptr<class Building> building);

    const class Resource &resource_by_id(const string &resource_id);

private:
    const Game &game;

    map<string, unique_ptr<class Resource>> resources;
    vector<tuple<unique_ptr<class Building>, int>> buildings;
};


#endif //LIFE_GAME_MANAGER_H
