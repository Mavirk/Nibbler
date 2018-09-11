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
	endwin();
	return ;
}

bool	Ncurses::init( int width, int height, int size ) {
	_size = size;
	_width = width / size;
	_height = height / size;
	_win = initscr();
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
			case KEY_EXIT:
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

	// render the boarder etc
	// top boarder
	// for ( int i = 0; i < _width; i++ ) {
	// 	mvwaddch(_win, 0, i, b);
	// }

	// // left boarder
	// for ( int i = 0; i < _height - 3; i++ ) {
	// 	mvwaddch(_win, i, 0, b);
	// }
	// // bottom boarder
	// for ( int i = 0; i < _height; i++ ) {
	// 	mvwaddch(_win, _width, i, b);
	// }
	// // right boarder
	// for ( int i = 0; i < _width; i++ ) {
	// 	mvwaddch(_win, i, _height, b);
	// }

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

	// process the snake
	std::vector<snakePart>	snakeTemp = snake.getSnake();
	for ( unsigned long i = 0; i < snakeTemp.size(); i++ ){
		mvwaddch(_win, snakeTemp[i].y/10, snakeTemp[i].x/10, s);
	}

	// print food to window
	move( _height - 1, 1 );
	printw( std::to_string(snake.food.x/10).c_str() );
	move( _height - 1, 6 );
	printw( std::to_string(snake.food.y/10).c_str() );
	move( snake.food.y/10, snake.food.x/10 );
	addch( f );
	refresh();
	return;
}

void	Ncurses::clean( void ) {
	std::cout << "Game cleaned" << std::endl;
}

bool	Ncurses::running( void ) {
	return this->_isRunning;
}