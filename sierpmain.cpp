// sierpmain.cpp
// main driver to test the Sierpinski fractal
// NOTE:
// you may only use this code if you fully understand how it works.
#include "gfx.h"
#include <cmath>
using namespace std;

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 );
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 );

int main()
{
  int width = 700, height = 700, mrgn = 20;

  gfx_open(width, height, "Sierpinski's Triangle");
  while(true) {
    gfx_clear();
    if( gfx_wait() == '1') {
		sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
	}
    if ( gfx_wait() == 'q' ) break;
  }
}

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  // Base case. 
  if( abs(x2-x1) < 5 ) return;

  // Draw the triangle
  drawTriangle( x1, y1, x2, y2, x3, y3 );

  // Recursive calls
  sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
  sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}

