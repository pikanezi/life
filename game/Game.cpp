//
// Created by Vincent Neel on 16/10/2023.
//

#include <chrono>
#include <thread>
#include <iostream>

#include "Game.h"

using namespace std;

void Game::start_simulation() {
    std::cout << "Game::start_simulation" << std::endl;
    is_running = true;
    thread simulation_thread(&Game::start, this);
    simulation_thread.detach();
}

void Game::stop_simulation() {
    std::cout << "Game::stop_simulation" << std::endl;
    is_running = false;
}

void Game::start() {
    cout << "Game::start" << std::endl;
    auto prev_time = now();
    this_thread::sleep_for(chrono::duration<double>(tick_delta_seconds));

    while (is_running) {
        auto current_time = now();
        update(chrono::duration<double>(current_time - prev_time).count());
        prev_time = current_time;
        this_thread::sleep_for(chrono::duration<double>(tick_delta_seconds));
    }
}

void Game::update(double delta_time) {
    cout << "Game::update " << delta_time << endl;
}
