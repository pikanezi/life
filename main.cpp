//
// Created by Vincent Neel on 16/10/2023.
//

#include <thread>
#include <iostream>
#include <fmt/core.h>

#include "game/Game.h"

int main() {
    Game game(0.2);
    game.load_buildings("resources/buildings.json");
    auto start = chrono::high_resolution_clock::now();
    game.start_simulation();
    game.manager.construct("farm");
    this_thread::sleep_for(3s);

    game.stop_simulation();
    std::cout << "simulation lasted "
              << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count()
              << "ms"
              << std::endl;
    std::cout << fmt::format("Finished with {} food\n", game.manager.resource_by_id("food").amount);

    return 0;
}