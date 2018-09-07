#include "Allegro.hpp"

extern "C" Allegro* create_object(){
  return new Allegro;
}

extern "C" void destroy_object( Allegro* object ){
	delete object;
}

Allegro::Allegro( void ) {
	this->_isRunning = true;
	this->_win = NULL;
	this->_eventQueue = NULL;
	std::cout << "Allegro made" << std::endl;
}

Allegro::Allegro( const Allegro& copy ) {
	*this = copy;
}

Allegro&	Allegro::operator=( const Allegro& rhs ) {
 	this->_win = rhs._win;
	this->_font = rhs._font;
	this->_eventQueue = rhs._eventQueue;
	this->_isRunning = rhs._isRunning;
	this->_size = rhs._size;
	this->maxWidth = rhs.maxWidth;
	this->maxHeight = rhs.maxHeight;
	return *this;
}

Allegro::~Allegro( void ) {
	return ;
}

void	Allegro::init( int width, int height, int size ) {
	ALLEGRO_MONITOR_INFO	info;

	this->maxWidth = width * 2;
	this->maxHeight = height * 2;
	this->_size = size * 2;

	// init allegro
	if ( !al_init() ) {
		std::cout << "Allegro not init" << std::endl;
		this->_isRunning = false;
	}

	// create game window
	this->_win = al_create_display( this->maxWidth, this->maxHeight );
	if ( !this->_win ) {
		std::cout << "Display was not created" << std::endl;
		this->_isRunning = false;
	}

	al_set_window_title( this->_win, "Snake Game Allegro" );
	al_get_monitor_info( 0, &info );
	al_set_window_position( this->_win, ( info.x2 - info.x1 ) / 2 - this->maxWidth / 2, ( info.y2 - info.y1 ) / 2 - this->maxHeight / 2 );

	// load font
	al_init_font_addon();
	al_init_ttf_addon();
	this->_font = al_load_font("OpenSans-ExtraBold.ttf", 36, 0 );
	if ( !this->_font ) {
		std::cout << "Could not load font" << std::endl;
		this->_isRunning = false;
	}

	// load addons
	al_install_keyboard();
	al_init_primitives_addon();

	this->_eventQueue = al_create_event_queue();
	al_register_event_source( this->_eventQueue, al_get_display_event_source( this->_win ) );
	al_register_event_source( this->_eventQueue, al_get_keyboard_event_source() );
}

char	Allegro::handleInput( void ) {
	ALLEGRO_EVENT	events;
	if (al_is_event_queue_empty( this->_eventQueue ) ) {
		return '\0';
	}
	al_wait_for_event( this->_eventQueue, &events );
	if ( events.type == ALLEGRO_EVENT_KEY_DOWN ) {
		switch ( events.keyboard.keycode ) {
			case ALLEGRO_KEY_LEFT:
				return 'l';
			case ALLEGRO_KEY_RIGHT:
				return 'r';
			case ALLEGRO_KEY_UP:
				return 'u';
			case ALLEGRO_KEY_DOWN:
				return 'd';
			case ALLEGRO_KEY_1:
				return '1';
			case ALLEGRO_KEY_2:
				return '2';
			case ALLEGRO_KEY_3:
				return '3';
			case ALLEGRO_KEY_ESCAPE:
				this->_isRunning = false;
				break ;
		}
	} else if ( events.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
		this->_isRunning = false;
	}

	return '\0';
}

void	Allegro::render( Snake& snake ) {
	al_clear_to_color( al_map_rgb( 150, 150, 150 ) );

	// draw to the screen --> back buffer
	std::vector<snakePart>		snakeTemp = snake.getSnake();
	for ( unsigned long i = 0; i < snakeTemp.size(); i++ ) {
		if ( i == 0 ) {
			al_draw_filled_rectangle( snakeTemp[i].x * 2, snakeTemp[i].y * 2, (snakeTemp[i].x * 2) + this->_size, (snakeTemp[i].y * 2) + this->_size, al_map_rgb( rand() % 255, rand() % 255, rand() % 255 ) );
		} else if ( i > 0 ) {
			al_draw_filled_rectangle( snakeTemp[i].x * 2, snakeTemp[i].y * 2, (snakeTemp[i].x * 2) + this->_size, (snakeTemp[i].y * 2) + this->_size, al_map_rgb( 255, 255, 255 ) );
		}
	}
	
	// draw food
	al_draw_filled_rectangle( snake.food.x * 2, snake.food.y * 2, (snake.food.x * 2) + this->_size, (snake.food.y * 2) + this->_size, al_map_rgb( 255, 0, 255 ) );

	// draw boarder to screen
	al_draw_filled_rectangle( 0, 0, this->_size, this->maxHeight, al_map_rgb( 0, 0, 0 ) ); // left boarder
	al_draw_filled_rectangle( 0, 0, this->maxWidth, this->_size, al_map_rgb( 0, 0, 0 ) ); // top boarder
	al_draw_filled_rectangle( (this->maxWidth - this->_size), 0, (this->maxWidth + this->_size), this->maxHeight, al_map_rgb( 0, 0, 0 ) ); // right boarder
	al_draw_filled_rectangle( 0, (this->maxHeight - (this->_size * 3) ), this->maxWidth, (this->maxHeight + (this->_size * 3) ), al_map_rgb( 0, 0, 0 ) ); // bottom boarder

	// display score
	std::string		score = "Score ";
	score += std::to_string( snake.score );
	al_draw_text( this->_font, al_map_rgb( 255, 255, 255 ), this->_size, this->maxHeight - (this->_size * 3), 0, score.c_str() );

	// flip back buffer to the screen
	al_flip_display();
}

bool	Allegro::running( void ) {
	return this->_isRunning;
}

void	Allegro::clean( void ) {
	al_destroy_event_queue( this->_eventQueue );
	al_destroy_display( this->_win );
}
