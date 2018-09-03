#include "sfml.hpp"
#include <iostream>

extern "C" SFML* create_object(){
  return new SFML;
}

extern "C" void destroy_object( SFML* object ){
  delete object;
}
SFML::~SFML(){
  return;
}

SFML::SFML(){
  _x = 20;
  _y = 20;
  return;
}

void SFML::printSquare(){
  std::cout << "I am sfml" << std::endl;
  std::cout << _x << std::endl;
  std::cout << _y << std::endl;
}