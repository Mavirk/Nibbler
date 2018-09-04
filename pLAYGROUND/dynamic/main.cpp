#include <iostream>
#include "game.hpp"

int main(int argc, char **argv)
{
    if (argc != 2){
        std::cout << "please try again" << std::endl;
        return 0;
    }
    Game game(argv);
    game.run();
}