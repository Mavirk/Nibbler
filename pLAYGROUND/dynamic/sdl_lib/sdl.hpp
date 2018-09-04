#ifndef SDL_HPP
#define SDL_HPP
#include "../IGraphics.hpp"
#include <SDL.h>
#include <iostream>
#include <string>


class SDL: public IGraphics{
public:
  SDL();
  virtual~SDL();
  /* use virtual otherwise linker will try to perform static linkage */
  void init();
  // int click;

private:
  int _x;
  int _y;
  SDL_Renderer* ren;
};

#endif