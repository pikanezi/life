//
// Created by Vincent Neel on 16/10/2023.
//

#include <thread>
#include <memory>
#include <fstream>
#include <iostream>
#include <fmt/core.h>

#include "Game.h"
#include "utils/IO.h"

using namespace std;

void Game::start_simulation() {
    cout << "Game::start_simulation" << endl;
    is_running = true;
    thread simulation_thread(&Game::start, this);
    simulation_thread.detach();
}

void Game::stop_simulation() {
    cout << "Game::stop_simulation" << endl;
    is_running = false;
}

void Game::start() {
    cout << "Game::start" << endl;
    auto prev_time = now();
    this_thread::sleep_for(chrono::duration<double>(tick_delta_seconds));

    while (is_running) {
        auto current_time = now();
        manager.update(chrono::duration<double>(current_time - prev_time).count());
        prev_time = current_time;
        this_thread::sleep_for(chrono::duration<double>(tick_delta_seconds));
    }
}

void Game::load_resources(const std::string &file_path) {
    auto resources = IO::read_file_as_json(file_path);

    for (const auto &resource: resources) {
        auto res = std::make_unique<class Resource>(Resource::from_json(resource));
        cout << fmt::format("resource {} loaded", res->id) << endl;
        manager.load_resource(std::move(res));
    }
}

void Game::load_buildings(const std::string &file_path) {
    const auto buildings = IO::read_file_as_json(file_path);

    for (const auto &i: buildings) {
        auto b = std::make_unique<class Building>(Building::from_json(i));
        cout << fmt::format("building {} loaded", b->id) << endl;
        manager.load_building(std::move(b));
    }
}
