#include <iostream>
#include "../Snake.hpp"
#include "../IGraphics.hpp"


#include <allegro5/allegro.h>
//#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

class Allegro : public IGraphics{
	private:
		ALLEGRO_DISPLAY*		_win;
		ALLEGRO_FONT*			_font;
		ALLEGRO_EVENT_QUEUE*	_eventQueue;
		bool					_isRunning;
		int						_size;

	public:
		int				maxWidth;
		int				maxHeight;

		Allegro( void );
		Allegro( const Allegro& copy );
		Allegro&	operator=( const Allegro& rhs );
		~Allegro( void );

		void	init( int width, int height, int size );
		bool	running( void );
		char	handleInput( void );
		void	render( Snake& snake );
		void	clean( void );
};

// makes the graphics based with Allegro