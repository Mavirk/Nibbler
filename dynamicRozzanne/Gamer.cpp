#include "Gamer.hpp"

Game::Game( void ) {}

Game::Game(char** argv, int width, int height, int size ) : _size( size ) {
    _width = width;
    _height = height;
	if (static_cast<std::string>(argv[1]) == "1")
        handle = dlopen("sdl.so", RTLD_LAZY);
    else if (static_cast<std::string>(argv[1]) == "2")
        handle = dlopen("sfml.so", RTLD_LAZY );
    if (!handle){
        std::cout << "bad handle" << std::endl;
        return ;
    }
    /* on Linux, use "./myclass.so" */
   	if ((create = reinterpret_cast<IGraphics* (*)()>(dlsym(handle, "create_object"))) == NULL) { 
        std::cerr << "creat_object : "<< dlerror() << std::endl;
        return ;
    }
    destroy = (void (*)(IGraphics*))dlsym(handle, "destroy_object");
    lib = create();
	this->input = '\0';
	this->_snake = Snake( width, height, this->_size );
	this->_snake.makeFood();
	this->delay = 200000;
}

Game::~Game( void ) {
	return ;
}

void
Game::run(){
	init( "Snake Game", _width / 2, _height / 2, _width, _height, false );
	while ( running() ) {
		handleEvents();
		update();
		render();
	}
	clean();
}

void
Game::loadLib(int i){
    const char* filename;
    switch (i) {
        case 1 :
            dlclose(handle);
            filename = "sdl.so";
            break;
        case 2 :
            dlclose(handle);
            filename = "sfml.so";
            break;
    }
    handle = dlopen(filename, RTLD_LAZY);
    if (!handle){
        std::cout << "bad handle" << std::endl;
        return;
    }else if ((create = reinterpret_cast<IGraphics* (*)()>(dlsym(handle, "create_object"))) == NULL){ 
        std::cerr << "create_object : "<< dlerror() << std::endl;
        return ;
    }
    destroy = (void (*)(IGraphics*))dlsym(handle, "destroy_object");
    lib = create();
}

void	Game::handleEvents( void ) {
	usleep( this->delay );
	this->input = lib->handleInput();
    std::cout << "input " << input << std::endl;
    switch(input){
        case '1':
            clean();
            loadLib(1);
            init( "sdl", _width, _height, _width, _height, false );
            break;
        case '2':
            clean();
            loadLib(2);
            init( "sfml", _width, _height, _width, _height, false );
            break;
        default:
            break;
    }
	this->_snake.moveSnake( this->input );
}

void	Game::init( std::string title, int xpos, int ypos, int width, int height, bool fullscreen ) {
	lib->init( title, xpos, ypos, width, height, fullscreen );
}

void	Game::update( void ) {
	lib->update();
	if ( (this->_snake.score % 100) == 0 ) {
		this->delay -= 1000;
	}
}

void	Game::render( void ) {
	lib->render( this->_snake );
}

void	Game::clean( void ) {
	lib->clean();
}

bool	Game::running( void ) {
	if ( this->_snake.collision() )
		return false;
	return lib->running();
}
