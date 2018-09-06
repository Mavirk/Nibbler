#include "Snake.hpp"

snakePart::snakePart( int col, int row ) {
	x = col;
	y = row;
}

snakePart::snakePart( void ) {
	x = 0;
	y = 0;
}

Snake::Snake( void ) {
	return ;
}

Snake::Snake( int maxX, int maxY, int size ) : _length( 5 ), _direction( 'l' ), _size( size ) {
	this->maxX = maxX - this->_size;
	this->maxY = maxY - (this->_size * 3);
	this->xPos = (((this->maxX / this->_size) / 2) * this->_size) - (this->_length * this->_size);
	this->yPos = (((this->maxY / this->_size) / 2) * this->_size);
	this->eat = false;
	this->score = 0;
	this->delay = 160000;

	for ( int i = 0; i < this->_length; i++ ) {
		snake.push_back( snakePart( this->xPos + (i * 10), this->yPos ) );
	}

	std::cout << "Snake made" << std::endl;
}

Snake::~Snake( void ) {
	return ;
}

void	Snake::moveSnake( char input ) {
	// get input... update direction
	if ( ( this->_direction == 'l' || this->_direction == 'r' ) && input != '\0' ) {
		if ( input == 'd' ) {
			// move down
			this->_direction = 'd';
		} else if ( input == 'u' ) {
			// move up
			this->_direction = 'u';
		}
	} else if ( ( this->_direction == 'u' || this->_direction == 'd') && input != '\0' ) {
		if ( input == 'l' ) {
			// move left
			this->_direction = 'l';
		} else if ( input == 'r' ) {
			// move right
			this->_direction = 'r';
		}
	}

	// moves the snake
	if ( this->_direction == 'l' ) {
		// move left
		snake.insert( snake.begin(), snakePart( snake[0].x - 10, snake[0].y ));
	} else if ( this->_direction == 'r' ) {
		// move right
		snake.insert( snake.begin(), snakePart( snake[0].x + 10, snake[0].y ));
	} else if ( this->_direction == 'u' ) {
		// move up
		snake.insert( snake.begin(), snakePart( snake[0].x, snake[0].y - 10 ));
	} else if ( this->_direction == 'd' ) {
		// move down
		snake.insert( snake.begin(), snakePart( snake[0].x, snake[0].y + 10 ));
	}

	// check for food
	if ( !this->eat ) {
		snake.pop_back();
	}
}

bool	Snake::collision( void ) {
	// check snake collision with the max window
	if ( snake[0].x < this->_size || snake[0].y < this->_size || snake[0].x == this->maxX || snake[0].y == this->maxY ) {
		return true;
	}

	// check snake collision with itself
	for ( unsigned int i = 2; i < snake.size(); i++ ) {
		if ( snake[0].x == snake[i].x && snake[0].y == snake[i].y )
			return true;
	}

	// check collision with food
	if ( snake[0].x == this->food.x && snake[0].y == this->food.y ) {
		// food eaten is true
		this->eat = true;
		this->score += 10;
		this->makeFood();
		if ( this->score % 100 == 0 ) {
			this->delay -= 20000;
			std::cout << "The delay is " << this->delay << std::endl;
		}
	} else {
		this->eat = false;
	}

	return false;
}

void	Snake::makeFood( void ) {
	bool	make = false;
	while ( !make ) {
		int		tempX = rand() % ( this->maxX/this->_size ) * this->_size;
		int		tempY = rand() % ( this->maxY/this->_size ) * this->_size;
		for ( unsigned int i = 0; i < snake.size(); i++ ){
			if ( snake[i].x == tempX && snake[i].y == tempY )
				continue ;
		}
		if ( tempX <= this->_size || tempY <= this->_size || tempX >= this->maxX || tempY >= this->maxY )
			continue ;
		this->food.x = tempX;
		this->food.y = tempY;
		make = true;
	}
}

int		Snake::getLength( void ) const {
	return this->_length;
}

int		Snake::getX( void ) const {
	return this->xPos;
}

int		Snake::getY( void ) const {
	return this->yPos;
}

std::vector<snakePart>	Snake::getSnake( void ) const {
	return this->snake;
}
