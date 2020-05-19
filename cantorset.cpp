// cantorset.cpp
// displays the cantor set fractal 
// at the position of your mouse click

#include "gfx.h"

void cantor( int x, int y, float len );

int main()
{
  int wd = 800, ht = 800;
  int length = 600;

  gfx_open(wd, ht, "cantor set");
  while(1) {
    if (gfx_wait() == 'q') break;
    gfx_clear();
    cantor(gfx_xpos(), gfx_ypos(), length);
  }

  return 0;
}

void cantor( int x, int y, float len )
{
   gfx_line(x, y, x+len, y);
   if(len < 2) return;      // base case
   y = y + 20;              // go 20 pixels below
   len = len/3;             // segment now 1/3

   // two recursive calls
   cantor(x, y, len);          // left segment
   cantor(x + 2*len, y, len);  // right segment
}

