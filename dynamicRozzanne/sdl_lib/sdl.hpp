#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#endif

#pragma once

#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../IGraphics.hpp"
#include "../Snake.hpp"

class SDL : public IGraphics{
	private:
		SDL_Window*		_win;
		SDL_Renderer*	_ren;
		SDL_Surface*	_surface;
		SDL_Texture*	_texture;
		TTF_Font*		_font;
		bool			_isRunning;
		int				_size;

	public:
		SDL_Rect		rect;
		int				maxWidth;
		int				maxHeight;

		SDL( void );
		SDL( const SDL& copy );
		SDL&	operator=( const SDL& rhs );
		~SDL( void );
		
		bool	init( int width, int height, int size );
		char	handleInput( void );
		void	render( Snake& snake );
		void	clean( void );

		void	drawRect( int x, int y );
		void	drawMessage( const char* msg, int x, int y, int r, int g, int b );
		bool	running( void );
};

// makes the graphics based on SDL