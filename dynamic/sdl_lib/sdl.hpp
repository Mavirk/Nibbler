#ifndef SDL_HPP
#define SDL_HPP
#include "../IGraphics.hpp"

class SDL: public IGraphics{
public:
  SDL();
  virtual~SDL();
  /* use virtual otherwise linker will try to perform static linkage */
  void printSquare();

private:
  int _x;
  int _y;
};

#endif