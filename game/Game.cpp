//
// Created by Vincent Neel on 16/10/2023.
//

#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>

#include "Game.h"
#include "utils/IO.h"

using namespace std;

void Game::start_simulation() {
    logger.log("Game::start_simulation");

    is_running = true;
    thread simulation_thread(&Game::start, this);
    simulation_thread.detach();
}

void Game::stop_simulation() {
    logger.log("Game::stop_simulation");

    is_running = false;
}

void Game::start() {
    logger.log("Game::start");

    auto prev_time = now();
    this_thread::sleep_for(chrono::duration<double>(tick_delta_seconds));

    while (is_running) {
        auto current_time = now();
        manager.update(chrono::duration<double>(current_time - prev_time).count());
        prev_time = current_time;
        this_thread::sleep_for(chrono::duration<double>(tick_delta_seconds));
    }
}

void Game::load_resources(std::string const &file_path) {
    auto resources = IO::read_file_as_json(file_path);

    for (auto const &resource: resources) {
        auto res = std::make_unique<class Resource>(Resource::from_json(resource));

        logger.log(fmt::format("resource {} loaded", res->id));
        manager.load_resource(std::move(res));
    }
}

void Game::load_buildings(std::string const &file_path) {
    auto const buildings = IO::read_file_as_json(file_path);

    for (auto const &i: buildings) {
        auto b = std::make_unique<class Building>(Building::from_json(i));

        logger.log(fmt::format("building {} loaded", b->id));
        manager.load_building(std::move(b));
    }
}
