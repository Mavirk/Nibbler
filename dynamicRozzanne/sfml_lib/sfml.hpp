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

class Graphics : public IGraphics{
	private:
		SDL_Window*		_win;
		SDL_Renderer*	_ren;
		SDL_Surface*	_surface;
		SDL_Texture*	_texture;
		TTF_Font*		_font;
		bool			_isRunning;

	public:
		SDL_Rect		rect;
		int				size;
		int				maxWidth;
		int				maxHeight;

		Graphics( void );
		// Graphics( std::string lib );
		// Graphics( const Graphics& copy );
		// Graphics&	operator=( const Graphics& rhs );
		~Graphics( void );

		void	init( std::string title, int xpos, int ypos, int width, int height, bool fullscreen );
		char	handleInput( void );
		void	update( void );
		void	render( Snake& snake );
		void	clean( void );

		void	drawRect( int x, int y );
		void	drawMessage( const char* msg, int x, int y, int r, int g, int b );
		bool	running( void );
};

// makes the graphics based on SDL