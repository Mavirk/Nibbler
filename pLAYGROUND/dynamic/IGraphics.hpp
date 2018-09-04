#ifndef IGRAPHICS_HPP
#define IGRAPHICS_HPP

class IGraphics{
public:
  IGraphics();
  virtual ~IGraphics();
  /* use virtual otherwise linker will try to perform static linkage */
  virtual void init() = 0;
};

#endif