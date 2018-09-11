#include "sdl.hpp"

extern "C" IGraphics* create_object(){
	std::cout << "Lib SDL Object created" << std::endl;
	return new SDL;
}

extern "C" void destroy_object( SDL* object ){
	delete object;
	std::cout << "Lib SDL Object destroyed" << std::endl;
}

SDL::SDL( void ) : _size( 10 ) {
	this->_win = NULL;
	this->_ren = NULL;
	this->_isRunning = true;
	this->_surface = NULL;
	this->_texture = NULL;
	this->_font = NULL;
	return ;
}

SDL::SDL( const SDL& copy ) {
	*this = copy;
}

SDL&	SDL::operator=( const SDL& rhs ) {
	this->_win = rhs._win;
	this->_ren = rhs._ren;
	this->_surface = rhs._surface;
	this->_texture = rhs._texture;
	this->_font = rhs._font;
	this->_isRunning = rhs._isRunning;
	this->_size = rhs._size;
	this->rect = rhs.rect;
	this->maxWidth = rhs.maxWidth;
	this->maxHeight = rhs.maxHeight;

	return *this;
}

SDL::~SDL( void ) {
	return ;
}

bool	SDL::init( int width, int height, int size ) {
	if ( SDL_Init(SDL_INIT_EVERYTHING) == 0 ) {
		std::cout << "Subsystems init" << std::endl;

		this->_win = SDL_CreateWindow( "Snake Game SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0 );
		if ( this->_win ) {
			this->maxWidth = width;
			this->maxHeight = height;
			this->_size = size;
			std::cout << "Window created" << std::endl;
		}

		this->_ren = SDL_CreateRenderer( this->_win, -1, 0 );
		if ( this->_ren ) {
			// set the render draw color
			SDL_RenderSetLogicalSize( this->_ren, width, height );
			SDL_SetRenderDrawColor( this->_ren, 255, 255, 255, 255 );
			std::cout << "Renderer created" << std::endl;
		}

		this->_isRunning = true;
	} else {
		this->_isRunning = false;
		return false;
	}

	if ( TTF_Init() == -1 ) {
		this->_isRunning = false;
		return false;
	}

	this->_font = TTF_OpenFont( "OpenSans-ExtraBold.ttf", 18 );
	if ( this->_font == NULL ) {
		this->_isRunning = false;
		return false;
	}

	return true;
}

char	SDL::handleInput( void ) {
	SDL_Event		event;
	SDL_PollEvent(&event);
	char			input = '\0';

	if ( event.type == SDL_QUIT ) {
		this->_isRunning = false;
		input = 'q';
	} else if ( event.type == SDL_KEYDOWN ) {
		switch ( event.key.keysym.sym ) {
			case SDLK_RIGHT:
				input = 'r';
				break ;
			case SDLK_LEFT:
				input = 'l';
				break ;
			case SDLK_DOWN:
				input = 'd';
				break ;
			case SDLK_UP:
				input = 'u';
				break ;
			case SDLK_1:
				input = '1';
				break ;
			case SDLK_2:
				input = '2';
				break ;
			case SDLK_3:
				input = '3';
				break ;
			case SDLK_ESCAPE:
				this->_isRunning = false;
				break ;
			default:
				break ;
		}
	}
	return input;
}

void	SDL::render( Snake& snake ) {
	// this is where we would add stuff to render
	SDL_RenderClear( this->_ren );

	// render the boarder etc
	SDL_SetRenderDrawColor( this->_ren, 0, 0, 0, 255 );
	// top boarder
	SDL_Rect	boarderTop = { 0, 0, this->maxWidth, this->_size };
	SDL_RenderFillRect( this->_ren, &boarderTop );
	// left boarder
	SDL_Rect	boarderLeft = { 0, 0, this->_size, this->maxHeight };
	SDL_RenderFillRect( this->_ren, &boarderLeft );
	// right boarder
	SDL_Rect	boarderRight = { this->maxWidth - this->_size, 0, this->_size, this->maxHeight };
	SDL_RenderFillRect( this->_ren, &boarderRight );
	// bottom boarder
	SDL_Rect	boarderBottom = { 0, this->maxHeight - (this->_size * 3), this->maxWidth, (this->_size * 3) };
	SDL_RenderFillRect( this->_ren, &boarderBottom );

	// process the snake
	std::vector<snakePart>	snakeTemp = snake.getSnake();
	SDL_SetRenderDrawColor( this->_ren, 0, 0, 255, 255 );
	for ( unsigned long i = 0; i < snakeTemp.size(); i++ ){
		if (i == 0)
			SDL_SetRenderDrawColor( this->_ren, 255, 255, 255, 255 );
		else
			SDL_SetRenderDrawColor( this->_ren, 0, 0, 255, 255 );
		drawRect( snakeTemp[i].x, snakeTemp[i].y );
		SDL_RenderFillRect( this->_ren, &rect );
	}

	// print food to window
	SDL_SetRenderDrawColor( this->_ren, 255, 0, 0, 255 );
	drawRect( snake.food.x, snake.food.y );
	SDL_RenderFillRect( this->_ren, &rect );

	std::string		score = "Score ";
	score += std::to_string( snake.score );
	drawMessage( score.c_str(), 20, this->maxHeight - 32, 255, 255, 255 );

	SDL_SetRenderDrawColor( this->_ren, 0, 255, 0, 255 );
	SDL_RenderPresent( this->_ren );
}

void	SDL::clean( void ) {
	TTF_Quit();
	SDL_DestroyWindow( this->_win );
	SDL_DestroyRenderer( this->_ren );
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

bool	SDL::running( void ) {
	return this->_isRunning;
}

void	SDL::drawRect( int x, int y ) {
	rect.x = x;
	rect.y = y;
	rect.w = this->_size;
	rect.h = this->_size;
}

void	SDL::drawMessage( const char* msg, int x, int y, int r, int g, int b ) {
	SDL_Color		color;
	SDL_Rect		rect;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	this->_surface = TTF_RenderText_Solid( this->_font, msg, color );
	this->_texture = SDL_CreateTextureFromSurface( this->_ren, this->_surface );
	rect.x = x;
	rect.y = y;
	rect.w = this->_surface->w;
	rect.h = this->_surface->h;
	SDL_FreeSurface( this->_surface );
	SDL_RenderCopy( this->_ren, this->_texture, NULL, &rect );
	SDL_DestroyTexture( this->_texture );
}

