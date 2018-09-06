#include "Gamer.hpp"

Game::Game( void ) {}

Game::Game(std::string l, int width, int height, int size ) : _size( size ) {
    _width = width;
    _height = height;
	if (l == "1")
        handle = dlopen("sdl.so", RTLD_LAZY);
    else if (l == "2")
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
	init(  _width , _height );
	while ( running() ) {
		handleEvents();
		render();
	}
	clean();
}

bool
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
        std::cout << "bd handle" << std::endl;
        return false;
    }else if ((create = reinterpret_cast<IGraphics* (*)()>(dlsym(handle, "create_object"))) == NULL){ 
        std::cerr << "create_object : "<< dlerror() << std::endl;
        return false;
    }
    destroy = (void (*)(IGraphics*))dlsym(handle, "destroy_object");
    lib = create();
    return true;
}

void	Game::handleEvents( void ) {
	usleep( this->delay );
	this->input = lib->handleInput();
    std::cout << "input " << input << std::endl;
    switch(input){
        case '1':
            clean();
            loadLib(1);
            init( _width, _height);
            break;
        case '2':
            clean();
            loadLib(2);
            init( _width, _height );
            break;
        default:
            break;
    }
	this->_snake.moveSnake( this->input );
}

void	Game::init( int height, int width) {
	lib->init( width, height, this->_size);
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
