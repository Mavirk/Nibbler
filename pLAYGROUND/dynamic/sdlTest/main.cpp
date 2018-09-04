#include <SDL.h>
#include <string>
#include <iostream>
#include <unistd.h>

SDL_Renderer*	init( std::string title ) {
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window*		win = SDL_CreateWindow(
		title.c_str(),
		100,
		100,
		640,
		480,
		SDL_WINDOW_SHOWN
	);
	SDL_Renderer*	ren = SDL_CreateRenderer(
		win,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	SDL_SetRenderDrawColor( ren, 0, 255, 0, 255 );
	SDL_RenderClear( ren );
	SDL_RenderPresent( ren );
	return ren;
}

int click(SDL_Renderer* ren){
	SDL_Event		event;
	int x, y;
	int quit = 0;
	if ( SDL_PollEvent( &event ) ) {
		if ( event.type == SDL_MOUSEBUTTONDOWN ) {
			SDL_SetRenderDrawColor( ren, 255, 255, 255, 255 );
			SDL_RenderClear( ren );
			SDL_GetMouseState( &x, &y );
			SDL_SetRenderDrawColor( ren, 255, 0, 0, 255 );
			SDL_RenderDrawPoint( ren, x, y );
			SDL_RenderPresent( ren );
		}
		if ( event.type == SDL_QUIT ) {
			quit = 1;
		} else if ( event.type == SDL_KEYDOWN ) {
			if ( event.key.keysym.sym == SDLK_ESCAPE ) {
				quit = 1;
			}
		}
	}
	std::cout << "test" << std::endl;
	return quit;
}

int		main( void ) {
	int quit = 0;
	SDL_Renderer*	ren = init( "Snake Game" );
	sleep(2);
	// while (quit == 0){
	// 	quit = click(ren);
	// }
	// SDL_Quit();
	return 0;
}
