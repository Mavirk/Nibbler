#include "game.hpp"

int main (int argc, char** argv){
    char** map;
    game g(argv);
    
    map = g.runFrame();
    

    return 0;
}
