#ifndef GAME_HPP
#define GAME_HPP
#endif

#pragma once

#include <iostream>
#include <unistd.h>
#include <dlfcn.h>

#include "Snake.hpp"
#include "IGraphics.hpp"

class Game {
	private:
		// Graphics	_gfx;
		Snake		_snake;
		int			_size;
		int			_width;
		int			_height;

	public:
		void* 		handle;
		IGraphics* 	lib;
		IGraphics* 	(*create)();
		void 		(*destroy)(IGraphics*);
		char		input;
		int			delay;

		Game( void );
		Game(std::string l, int width, int height, int size );
		//Game( std::string gfx, int width, int height );
		~Game( void );

		void	run();
		bool 	loadLib(int i);
		
		void	init(  int width, int height );
		void	handleEvents( void );
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