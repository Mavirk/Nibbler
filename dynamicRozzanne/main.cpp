#include <iostream>
#include <string>
#include "Game.hpp"
// #include <allegro5/allegro.h>

Game*	game = nullptr;

bool checkArgs(char** av){
	std::string		width(av[1]);
	std::string		height(av[2]);
	std::string 	lib(av[3]);
	
	int w = std::stoi(width), h = std::stoi(height), l = std::stoi(lib);

	if (l != 1 && l != 2  && l != 3)
		return false;
	else if (w < 300 || w > 1200)
		return false;
	else if (h < 300 || h > 900)
		return false;
	return true;
}

int		main(int argc, char **argv) {
	int		size = 10;
    if (argc == 4 && checkArgs(argv)){
		int				width = std::stoi(argv[1]);
		int				height = std::stoi(argv[2]);
		std::string 	lib(argv[3]);
		game = new Game(lib, width, height, size);
		if ( !game->init() ) {
        	std::cerr << "Error: Could not create game loop." << std::endl;
		} else {
			game->run();
		}
		delete game;
		return 1;
    } else {
        std::cout << "Too few arguments --> " << std::endl;
		std::cout << "Use: ./nibbler width height and library" << std::endl;
		std::cout << "Library: can be given in 1, 2 or 3" << std::endl;
	}
	return 0;
}