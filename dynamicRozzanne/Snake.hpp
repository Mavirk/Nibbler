#ifndef SNAKE_HPP
#define SNAKE_HPP
#endif

#pragma once

#include <iostream>
#include <string>
#include <vector>
//#include "Board.hpp"

struct snakePart {
	int		x;
	int		y;
	snakePart( int col, int row );
	snakePart();
};

class Snake {
	private:
		int			_length;
		char		_direction;
		int			_size;

	public:
		std::vector<snakePart>	snake;
		int			xPos;
		int			yPos;
		int			maxX;
		int			maxY;
		snakePart	food;
		bool		eat;
		int			score;
		int			delay;

		Snake( void );
		Snake( int maxX, int maxY, int size );
		~Snake( void );

		void	moveSnake( char input );
		bool	collision( void );
		void	makeFood( void );

		std::vector<snakePart>	getSnake( void ) const;
		int		getLength( void ) const;
		int		getX( void ) const;
		int		getY( void ) const;

};