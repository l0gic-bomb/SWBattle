
#include "GameObjects/Game.hpp"
#include <iostream>
#include <fstream>


int main(int argc, char** argv)
{
    if (argc != 2) {
        throw std::runtime_error("Error: No file specified in command line argument");
    }

    std::ifstream file(argv[1]);
    if (!file) {
        throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
    }

    std::unique_ptr<sw::game::Game> game = std::make_unique<sw::game::Game>();
    game->initGame(file);

    while (true) {
        if (game->isGameFinished())
            break;
        game->update();
    }

    std::cout << "Game is finished";
	return 0;
}