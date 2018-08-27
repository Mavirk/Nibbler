#ifndef SNAKE_HPP
#define SNAKE_HPP
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
struct snakepart{
    int x;
    int y;
    snakepart(int col, int row);
    snakepart();

};

class snakeClass{
    private:
        int points, delay, maxWidth, maxHeight;
        char direction, partchar, edgechar, foo;
        bool grow;
        snakepart food;
        std::vector<snakepart> snake;
        void putfood();
        bool collision();
        void moveSnake();
    public:
        snakeClass();
        ~snakeClass();
        void run();
};
#endif