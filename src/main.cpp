#include "../include/game.h"
#include <iostream>

int main() {
    Game* game = new Game();

    // Game loop
    while (game->isRunning()) {
        // Update
        game->update();
        // Render
        game->render();
    }

    delete game;
    return 0;
}
