#include <iostream>
#include <string>
#include "includes/Game.hpp"

Game*	game = nullptr;

int		main(int argc, char **argv) {
    if (argc != 2){
        std::cout << "please try again" << std::endl;
        return 0;
    }

	int		width = 480;
	int		height = 240;
	int		size = 10;
	game = new Game(argv, width, height, size );
	game.run();
	return 0;
}