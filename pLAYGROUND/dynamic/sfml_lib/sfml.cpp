#include "sfml.hpp"

extern "C" SFML* create_object(){
  return new SFML;
}

extern "C" void destroy_object( SFML* object ){
  delete object;
}
SFML::SFML(){
  _x = 20;
  _y = 20;
  return;
}
SFML::~SFML(){
  SDL_Quit();
  return;
}



void
SFML::init(){
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
	SDL_SetRenderDrawColor( ren, 0, 255, 0, 255 );
	SDL_RenderClear( ren );
	SDL_RenderPresent( ren );
}












































    // // create the window

    // sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // // run the program as long as the window is open
    // while (window.isOpen())
    // {
    //     // check all the window's events that were triggered since the last iteration of the loop
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         // "close requested" event: we close the window
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     // clear the window with black color
    //     window.clear(sf::Color::Black);

    //     // draw everything here...
    //     // window.draw(...);

    //     // end the current frame
    //     window.display();
    // }