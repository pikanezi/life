//
// Created by Vincent Neel on 16/10/2023.
//

#ifndef LIFE_GAME_H
#define LIFE_GAME_H

#include <chrono>
#include <memory>

using namespace std;

class Game {

public:
    Game() : tick_delta_seconds(0.25) {};

    explicit Game(const double tickDeltaSeconds) : tick_delta_seconds(tickDeltaSeconds) {}

public:
    void start_simulation();

    void stop_simulation();


private:
    void start();

    void update(double delta_time);

protected:
    bool is_running = false;
    const double tick_delta_seconds;

private:
    chrono::time_point<chrono::steady_clock> now() { return chrono::steady_clock::now(); }
};

#endif //LIFE_GAME_H
