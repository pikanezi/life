//
// Created by Vincent Neel on 16/10/2023.
//

#include <chrono>
#include <thread>
#include <iostream>

#include "game/Game.h"

int main() {
    Game game(0.2);
    auto start = chrono::high_resolution_clock::now();
    game.start_simulation();
    this_thread::sleep_for(3s);

    game.stop_simulation();
    std::cout << "simulation lasted "
              << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count()
              << "ms"
              << std::endl;
    return 0;
}