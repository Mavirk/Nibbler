#include "sdl.hpp"
#include <iostream>

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
    return;
}
void SDL::printSquare(){
  std::cout << "I am sdl" << std::endl;
  std::cout << _x << std::endl;
  std::cout << _y << std::endl;
}