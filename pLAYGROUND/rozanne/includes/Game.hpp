#ifndef GAME_HPP
#define GAME_HPP
#endif

#pragma once

#include <iostream>
#include <unistd.h>
#include "Snake.hpp"
#include "IGraphics.hpp"

class Game {
	private:
		Graphics	_gfx;
		Snake		_snake;
		int			_size;

	public:
		char		input;
		int			delay;

		Game( void );
		Game(char** argv, int width, int height, int size );
		//Game( std::string gfx, int width, int height );
		~Game( void );

		void	run();
		void	handleEvents( void );
		void	init( std::string title, int xpos, int ypos, int width, int height, bool fullscreen );
		void	update( void );
		void	render( void );
		void	clean( void );

		bool	running( void );
};

// holds the board info
	// size --> width and height
	// score

// holds the graphics class
	// sends update info for graphics if key is pressed

// grabs the input keys
	// gets user input and relays that to graphics

// holds the character class
	// holds the char x & y co-ordinates
	// holds the direction
	// size