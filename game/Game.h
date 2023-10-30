//
// Created by Vincent Neel on 16/10/2023.
//

#ifndef LIFE_GAME_H
#define LIFE_GAME_H

#include <chrono>
#include <memory>
#include <string>

#include "./utils/Logger.h"
#include "GameManager.h"

using namespace std;

class Game {

public:
    Game() : tick_delta_seconds(0.25), manager(GameManager(*this)){};

    explicit Game(double const tickDeltaSeconds) : tick_delta_seconds(tickDeltaSeconds), manager(GameManager(*this)){};

public:
    void start_simulation();

    void stop_simulation();

    void load_resources(string const &file_path);

    void load_buildings(string const &file_path);

private:
    void start();

public:
    bool is_running = false;
    double const tick_delta_seconds;
    Logger logger;

    GameManager manager;

private:
    chrono::time_point<chrono::steady_clock> now() { return chrono::steady_clock::now(); }
};

#endif//LIFE_GAME_H
