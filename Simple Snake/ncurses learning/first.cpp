#include <ncurses.h>

int main (){
    initscr();
    printw("hello World");
    refresh();
    getch();
    endwin();
    return (0);
}