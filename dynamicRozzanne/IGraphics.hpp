#ifndef IGRAPHICS_HPP
#define IGRAPHICS_HPP

#include "Snake.hpp"

class IGraphics{
  public:
    virtual ~IGraphics( void ) {}

    /* use virtual otherwise linker will try to perform static linkage */
    virtual bool	init( int width, int height, int size ) = 0;
    virtual char	handleInput( void ) = 0;
    virtual void	render( Snake& snake ) = 0;
    virtual void	clean( void ) = 0;
    virtual bool  running () = 0;
};

#endif