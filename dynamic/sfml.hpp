#ifndef SFML_HPP
#define SFML_HPP
#include "IGraphics.hpp"
class SFML : public IGraphics{
public:
  SFML();
  virtual ~SFML();
  /* use virtual otherwise linker will try to perform static linkage */
  void printSquare();

private:
  int _x;
  int _y;
};

#endif