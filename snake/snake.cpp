#include "snake.hpp"

snakepart::snakepart(int col, int row){
    x = col;
    y = row;
}

snakepart::snakepart(){
    x = 0;
    y = 0;
}

snakeClass::snakeClass(){
    initscr();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    getmaxyx(stdscr,maxHeight,maxWidth);
    partchar = 'x';
    edgechar = '#';
    foo = '*';
    food.x = 0;
    food.y = 0;
    for (int i = 0 ; i < 5; i++)
        snake.push_back(snakepart(40 + i, 10));
    points = 0;
    delay = 110000;
    grow = false;
    direction = 'l';
    srand(time(0));
    for(int i = 0; i < maxWidth - 1; i++){ //drawing the top border
         move(0, i);
         addch(edgechar);
    }
    for(int i = 0; i < maxHeight - 2; i++){ //drawing the right border
         move(i ,maxWidth - 1);
         addch(edgechar);
    }
    for(int i = 0; i < maxWidth - 1; i++){ //drawing the bottom border
         move(maxHeight - 2, i);
         addch(edgechar);
    }
    for(int i = 0; i < maxHeight - 2; i++){ //drawing the left border
         move(i, 0);
         addch(edgechar);
    }
    for(size_t i = 0; i < snake.size(); i++){ //drawing the snake
        move(snake[i].y,snake[i].x);
        addch(partchar);
    }
    putfood(); // drawing the food
    move(maxHeight - 1, 0);
    printw("%d", points);
    refresh();
}

snakeClass::~snakeClass(){
    nodelay(stdscr,false);
    getch();
    endwin();
}

void snakeClass::putfood(){
    while(1){
        int tmpx = rand()%maxWidth +1;
        int tmpy = rand()%maxHeight +1;
        for (size_t i = 0;i < snake.size(); i++){
            if(snake[i].x == tmpx && snake[i].y == tmpy)
                continue;
        }
        if(tmpx >= maxWidth - 2 || tmpy >= maxHeight - 3)
            continue;
        food.x = tmpx;
        food.y = tmpy;
        break;
    }
    move(food.y, food.x);
    addch(foo);
    refresh();
}

bool snakeClass::collision(){
    if(snake[0].x == 0 || snake[0].x == maxWidth-1 ||
    snake[0].y == 0 || snake[0].y == maxHeight - 2)
        return true;
    for(size_t i = 1;i < snake.size();i++)
        if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            return true;
    if(snake[0].x == food.x && snake[0].y == food.y){
        grow = true;
        putfood();
        points += 10;
        move(maxHeight - 1,0);
        printw("%d", points);
        if ((points %100) == 9)
            delay -= 10000;
    }else
        grow = false;
    return false;
}

void snakeClass::moveSnake(){
    int tmp = getch();
    switch(tmp){
        case KEY_LEFT:
            if (direction != 'r')
                direction = 'l';
            break;
        case KEY_RIGHT:
            if (direction != 'l')
                direction = 'r';
            break;
        case KEY_UP:
            if (direction != 'd')
                direction = 'u';
            break;
        case KEY_DOWN:
            if (direction != 'u')
                direction = 'd';
            break;
        case KEY_BACKSPACE:
            direction = 'q';
            break;
        default:
            break;
    }

    if(!grow){
        move(snake[snake.size() - 1].y, snake[snake.size() - 1].x);
        addch(' ');
        refresh();
        snake.pop_back();
    }

    if (direction == 'l')
        snake.insert(snake.begin(), snakepart(snake[0].x-1, snake[0].y));
    else if (direction == 'r')
        snake.insert(snake.begin(), snakepart(snake[0].x+1, snake[0].y));
    else if (direction == 'u')
        snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y-1));
    else if (direction == 'd')
        snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y+1));
    move(snake[0].y, snake[0].x);
    addch(partchar);
    refresh();
}

void snakeClass::run(){
    while (1){
        if(collision()){
            move(maxWidth/2 - 4, maxHeight/2);
            printw("game over");
            break;
        }
        moveSnake();
        if(direction == 'q')
            break;
        usleep(delay);
    }
}
