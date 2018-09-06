#ifndef SFML_HPP
#define SFML_HPP
#endif

#pragma once

#include <iostream>
#include "../Snake.hpp"
#include "../IGraphics.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class SFML : public IGraphics{
	private:
		sf::RenderWindow*	_win;
		sf::Font			_font;
		bool			_isRunning;
		int				_size;

	public:
		int				maxWidth;
		int				maxHeight;

		SFML( void );
		SFML( const SFML& copy );
		SFML&	operator=( const SFML& rhs );
		~SFML( void );

		void	init( int width, int height, int size );
		bool	running( void );
		char	handleInput( void );
		void	render( Snake& snake );
		void	clean( void );
};
