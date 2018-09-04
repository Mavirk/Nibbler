#include "sdl.hpp"

extern "C" SDL* create_object(){
  return new SDL;
}

extern "C" void destroy_object( SDL* object ){
  delete object;
}

SDL::SDL(){
  _x = 20;
  _y = 20;
  return;
}
SDL::~SDL(){
    SDL_Quit();
    return;
}

void
SDL::init(){
  std::string title = "SDL";
  SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window*		win = SDL_CreateWindow(
    title.c_str(),
		100,
		100,
		640,
		480,
		SDL_WINDOW_SHOWN
	);
	ren = SDL_CreateRenderer(
		win,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	SDL_SetRenderDrawColor( ren, 255, 0, 0, 255 );
	SDL_RenderClear( ren );
	SDL_RenderPresent( ren );
}