#include "sdl.hpp"

extern "C" Graphics* create_object(){
  return new Graphics;
}

extern "C" void destroy_object( Graphics* object ){
  delete object;
}

Graphics::Graphics( void ) : size( 10 ) {
	this->_win = NULL;
	this->_ren = NULL;
	this->_isRunning = true;
	this->_surface = NULL;
	this->_texture = NULL;
	this->_font = NULL;
	return ;
}

// Graphics::Graphics( const Graphics& copy ) {

// }

// Graphics&	Graphics::operator=( const Graphics& rhs ) {

// }

Graphics::~Graphics( void ) {
	SDL_Quit();
	return ;
}

void	Graphics::init( std::string title, int xpos, int ypos, int width, int height, bool fullscreen ) {
	int		flags = 0;
	if ( fullscreen )
		flags = SDL_WINDOW_FULLSCREEN;

	if ( SDL_Init(SDL_INIT_EVERYTHING) == 0 ) {
		std::cout << "Subsystems init" << std::endl;

		this->_win = SDL_CreateWindow( title.c_str(), xpos, ypos, width, height, flags );
		if ( this->_win ) {
			this->maxWidth = width;
			this->maxHeight = height;
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
	}

	if ( TTF_Init() == -1 ) {
		this->_isRunning = false;
	}

	this->_font = TTF_OpenFont( "OpenSans-ExtraBold.ttf", 18 );
	if ( this->_font == NULL )
		this->_isRunning = false;
}

char	Graphics::handleInput( void ) {
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
			default:
				break ;
		}
	}

	return input;
}

void	Graphics::update( void ) {
	return ;
}

void	Graphics::render( Snake& snake ) {
	// this is where we would add stuff to render
	SDL_RenderClear( this->_ren );

	// render the boarder etc
	SDL_SetRenderDrawColor( this->_ren, 0, 0, 0, 255 );
	// top boarder
	SDL_Rect	boarderTop = { 0, 0, this->maxWidth, 10 };
	SDL_RenderFillRect( this->_ren, &boarderTop );
	// left boarder
	SDL_Rect	boarderLeft = { 0, 0, 10, this->maxHeight };
	SDL_RenderFillRect( this->_ren, &boarderLeft );
	// right boarder
	SDL_Rect	boarderRight = { this->maxWidth - 10, 0, 10, this->maxHeight };
	SDL_RenderFillRect( this->_ren, &boarderRight );
	// bottom boarder
	SDL_Rect	boarderBottom = { 0, this->maxHeight - 30, this->maxWidth, 30 };
	SDL_RenderFillRect( this->_ren, &boarderBottom );

	// process the snake
	std::vector<snakePart>	snakeTemp = snake.getSnake();
	SDL_SetRenderDrawColor( this->_ren, 0, 0, 255, 255 );
	for ( unsigned long i = 0; i < snakeTemp.size(); i++ ){
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

void	Graphics::clean( void ) {
	TTF_Quit();
	SDL_DestroyWindow( this->_win );
	SDL_DestroyRenderer( this->_ren );
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

bool	Graphics::running( void ) {
	return this->_isRunning;
}

void	Graphics::drawRect( int x, int y ) {
	rect.x = x;
	rect.y = y;
	rect.w = this->size;
	rect.h = this->size;
}

void	Graphics::drawMessage( const char* msg, int x, int y, int r, int g, int b ) {
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