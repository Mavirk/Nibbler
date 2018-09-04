#ifndef SFML_HPP
#define SFML_HPP
#include "../IGraphics.hpp"
#include <SDL.h>
#include <iostream>
class SFML : public IGraphics{
public:
  SFML();
  virtual ~SFML();
  /* use virtual otherwise linker will try to perform static linkage */
  void init();

private:
  int _x;
  int _y;
  SDL_Renderer* ren;
};

#endif