#include <iostream>
#include "../Snake.hpp"
#include "../IGraphics.hpp"
#include <ncurses.h>

class Ncurses : public IGraphics{
	private:
		int		_size;
		int		_width;
		int		_height;
		WINDOW* _win;
		// SCREEN* screen;
		char	_input;
		bool	_isRunning;
	public:
		Ncurses( void );
		Ncurses( const Ncurses& copy );
		Ncurses&	operator=( const Ncurses& rhs );
		~Ncurses( void );

		bool	init( int width, int height, int size );
		bool	running( void );
		char	handleInput( void );
		void	render( Snake& snake );
		void	clean( void );
};

// makes the graphics based with Ncurses