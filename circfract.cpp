// circfract.cpp
// fractal of recursively drawn circles of various radii

#include "gfx.h"
#include <unistd.h>

void draw_circles( float x, float y, float r );

int main()
{
  int wd = 600, ht = 600, radius = 200;

  gfx_open(wd, ht, "concentric circles");

  while(1) {
    gfx_clear();
    draw_circles(wd/2, ht/2, radius);
    if (gfx_wait() == 'q') break;
  }
}

void draw_circles( float x, float y, float r )
{
   gfx_circle(x, y, r);    // draw a circle
   gfx_flush();
   usleep(5000);  // change value to slow down or speed up

   if( r < 5 ) return;     // base case
   r = r*0.5;              // reduce radius by half
   draw_circles(x + r, y, r);   // recursion call
   draw_circles(x - r, y, r);   // recursion call
}

// you can add a couple more calls to draw circules abover and below

