#include "ncurses.hpp"

extern "C" IGraphics* create_object(){
	std::cout << "Lib Ncurses Object created" << std::endl;
	return new Ncurses;
}

extern "C" void destroy_object( Ncurses* object ){
	delete object;
	std::cout << "Lib Ncurses Object destroyed" << std::endl;
}

Ncurses::Ncurses( void ) {
	_isRunning = true;
	return ;
}

Ncurses::Ncurses( const Ncurses& copy ) {
	*this = copy;
	return ;
}

Ncurses&	Ncurses::operator=( const Ncurses& rhs ) {
	_win = rhs._win;
	_input = rhs._input;
	_isRunning = rhs._isRunning;
	_width = rhs._width;
	_height = rhs._height;
	_size = rhs._size;
	return *this;
}

Ncurses::~Ncurses( void ) {
	refresh();
	endwin();
	return ;
}

bool	Ncurses::init( int width, int height, int size ) {
	_size = size;
	_width = width / size;
	_height = height / size;
	_win = initscr();
	if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		return false;
	}
    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho();
    curs_set(0);

	return true;
}

char	Ncurses::handleInput( void ) {
		switch (getch()) {
			case KEY_RIGHT:
				_input = 'r';
				break ;
			case KEY_LEFT:
				_input = 'l';
				break ;
			case KEY_DOWN:
				_input = 'd';
				break ;
			case KEY_UP:
				_input = 'u';
				break ;
			case '1':
				_input = '1';
				break ;
			case '2':
				_input = '2';
				break ;
			case '3':
				_input = '3';
				break ;
			case 27:
				this->_isRunning = false;
				break ;
			default:
				break ;
		}
	return _input;
}

void	Ncurses::render( Snake& snake ) {
	clear();
	char s = 'x';
	char f = '*';
	char b = '#';
	// this is where we would add stuff to render

	start_color();
	init_pair(FOOD_PAIR, COLOR_GREEN, COLOR_GREEN);
	init_pair(SCORE_PAIR, COLOR_CYAN, COLOR_BLACK);
	init_pair(MOUNTAIN_PAIR, COLOR_WHITE, COLOR_WHITE);
	init_pair(SNAKE_PAIR, COLOR_MAGENTA, COLOR_MAGENTA);

	wattron(_win, COLOR_PAIR(MOUNTAIN_PAIR));
	for ( int i = 0; i < _width; i++ ) {
		
		move( 0, i );
		addch( b );
	}
	for ( int i = 0; i < _height; i++ ) {
		move( i, 0 );
		addch( b );
	}
	for ( int i = 0; i < _width; i++ ) {
		move( (_height - 3), i );
		addch( b );
	}
	for ( int i = 0; i < _height; i++ ) {
		move( i, _width );
		addch( b );
	}
	attroff(COLOR_PAIR(MOUNTAIN_PAIR));

	// process the snake
	wattron(_win, COLOR_PAIR(SNAKE_PAIR));
	std::vector<snakePart>	snakeTemp = snake.getSnake();
	for ( unsigned long i = 0; i < snakeTemp.size(); i++ ){
		mvwaddch(_win, snakeTemp[i].y/10, snakeTemp[i].x/10, s);
	}
	attroff(COLOR_PAIR(SNAKE_PAIR));

	// print score to window
	wattron(_win, COLOR_PAIR(SCORE_PAIR));
	move( _height - 1, 2 );
	printw( "Score " );
	move( _height - 1, 8 );
	printw( std::to_string(snake.score).c_str() );
	wattron(_win, COLOR_PAIR(SCORE_PAIR));

	// print food to window
	wattron(_win, COLOR_PAIR(FOOD_PAIR));
	move( snake.food.y/10, snake.food.x/10 );
	addch( f );
	wattron(_win, COLOR_PAIR(FOOD_PAIR));
	refresh();
	return;
}

void	Ncurses::clean( void ) {
	std::cout << "Game cleaned" << std::endl;
}

bool	Ncurses::running( void ) {
	return this->_isRunning;
}