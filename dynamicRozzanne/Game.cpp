#include "Game.hpp"

Game::Game( void ) {
    return ;
}

Game::Game( std::string libInput, int width, int height, int size ) : _size( size ), _width( width ), _height( height ) {
    if ( libInput == "1" ){
        handle = dlopen( "sdl.so", RTLD_LAZY );
        std::cout << "Library made is #" << libInput << std::endl;
    } else if ( libInput == "2" ){
        handle = dlopen( "sfml.so", RTLD_LAZY );
        std::cout << "Library made is #" << libInput << std::endl;
    } else if (libInput == "3" ){
        handle = dlopen( "ncur.so", RTLD_LAZY );
        std::cout << "Library made is #" << libInput << std::endl;
    }

    if (!handle){
        std::cerr << "Error: Bad handle." << dlerror() << std::endl;
        return ;
    }
    /* on Linux, use "./myclass.so" */
   	if ((create = reinterpret_cast<IGraphics* (*)()>(dlsym(handle, "create_object"))) == NULL) { 
        std::cerr << "Creat_object : "<< dlerror() << std::endl;
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
    destroy( lib );
    dlclose( handle );
	return ;
}

void    Game::run(){
    while ( running() ) {
        handleEvents();
        render();
    }
    clean();
}

bool    Game::loadLib(int i){
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
        case 3 :
            dlclose(handle);
            filename = "ncur.so";
            break;
    }
    handle = dlopen(filename, RTLD_LAZY);
    if (!handle){
        std::cerr << "Error: Bad handle." << std::endl;
        return false;
    } else if ((create = reinterpret_cast<IGraphics* (*)()>(dlsym(handle, "create_object"))) == NULL){ 
        std::cerr << "Create_object : "<< dlerror() << std::endl;
        return false;
    }
    destroy = (void (*)(IGraphics*))dlsym(handle, "destroy_object");
    lib = create();
    std::cout << "Library loaded is #" << i << std::endl;
    return true;
}

void	Game::handleEvents( void ) {
	usleep( this->_snake.delay );
	this->input = lib->handleInput();
    // std::cout << "input " << input << std::endl;
    switch(input){
        case '1':
            clean();
            loadLib(1);
            init();
            break;
        case '2':
            clean();
            loadLib(2);
            init();
            break;
        case '3':
            clean();
            loadLib(3);
            init();
            break;
        default:
            break;
    }
	this->_snake.moveSnake( this->input );
}

bool	Game::init( void ) {
	if ( !lib->init( this->_width, this->_height, this->_size) ) {
        std::cerr << "Error: Library window could not be initiated." << std::endl;
        return false;
    }

    return true;
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
