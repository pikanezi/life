#include <memory>

#include "game/Game.h"
#include "library.h"

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

void load_buildings(char const *file_path) {
    game->load_buildings(file_path);
}