#include "../includes/Game.hpp"

Game::Game( void ) {}

Game::Game(char** argv, int width, int height, int size ) : _size( size ) {
	this->input = '\0';
	this->_gfx = Graphics();
	this->_snake = Snake( width, height, this->_size );
	this->_snake.makeFood();
	this->delay = 200000;
}

Game::~Game( void ) {
	return ;
}
void
Game::run(){
	init( "Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false );
	while ( running() ) {
		handleEvents();
		update();
		render();
	}
	clean();
}
void	Game::handleEvents( void ) {
	usleep( this->delay );
	this->input = this->_gfx.handleInput();
	this->_snake.moveSnake( this->input );
}

void	Game::init( std::string title, int xpos, int ypos, int width, int height, bool fullscreen ) {
	this->_gfx.init( title, xpos, ypos, width, height, fullscreen );
}

void	Game::update( void ) {
	this->_gfx.update();
	if ( (this->_snake.score % 100) == 0 ) {
		this->delay -= 1000;
	}
}

void	Game::render( void ) {
	this->_gfx.render( this->_snake );
}

void	Game::clean( void ) {
	this->_gfx.clean();
}

bool	Game::running( void ) {
	if ( this->_snake.collision() )
		return false;
	return this->_gfx.running();
}
