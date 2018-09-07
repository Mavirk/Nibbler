#include <iostream>
#include <string>
#include "Gamer.hpp"

Game*	game = nullptr;
bool checkArgs(char** av){
	std::string		width(av[1]);
	std::string		height(av[2]);
	std::string 	lib(av[3]);
	
	int w = std::stoi(width), h = std::stoi(height), l = std::stoi(lib);

	if (l != 1 && l != 2  && l != 3)
		return false;
	else if (w < 300 || w > 900)
		return false;
	else if (h < 300 || h > 900)
		return false;
	return true;
}

int		main(int argc, char **argv) {
	int		size = 10;
    if (argc == 4 && checkArgs(argv)){
		std::string		width(argv[1]);
		std::string		height(argv[2]);
		std::string 	lib(argv[3]);
		game = new Game(lib, std::stoi(width), std::stoi(height), size);
		game->run();
		delete game;
		return 1;
    }else
        std::cout << "please try again" << std::endl;
	return 0;
}