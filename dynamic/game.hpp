#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>
#include <dlfcn.h>
#include "IGraphics.hpp"


class Game {
    public:
    Game(char** argv);
    ~Game();
    void run();
    void loadLib(int i);
    
    char lastKey;
    void* handle;
    IGraphics* lib;
    IGraphics* (*create)();
    void (*destroy)(IGraphics*);

};
#endif