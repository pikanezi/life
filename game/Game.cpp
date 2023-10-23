//
// Created by Vincent Neel on 16/10/2023.
//

#include <thread>
#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include <json/json.h>

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

void Game::load_buildings(const std::string &file_path) {
    auto file_content = IO::read_file(file_path);
    Json::CharReaderBuilder builder{};
    auto reader = std::unique_ptr<Json::CharReader>(builder.newCharReader());
    Json::Value root{};
    std::string errors{};
    const auto is_parsed = reader->parse(file_content.c_str(),
                                         file_content.c_str() + file_content.length(),
                                         &root,
                                         &errors);
    if (!is_parsed) {
        cerr << "ERROR: Could not parse! " << errors << endl;
        return;
    }
    for (const auto & i : root) {
        manager.load_building(Building::from_json(i));
    }
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
