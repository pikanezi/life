#include <memory>

#include "library.h"
#include "game/Game.h"

std::shared_ptr<Game> game;

void initialize_game(double tick_delta_seconds) {
    game = std::make_shared<Game>(0.25);
}
void start_simulation() {
    game->start_simulation();
}

void stop_simulation() {
    game->stop_simulation();
}

void load_buildings(const char* file_path) {
    game->load_buildings(file_path);
}