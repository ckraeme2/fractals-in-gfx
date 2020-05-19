// Charles Kraemer
#include "gfx.h"
#include <cmath>
using namespace std;

void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void shrink(int x, int y, float s);
void squareSpiral(int x, int y, float r, float s, float a);
void lace(int x,int y,float r);
void snowflake(float x,float y,float s);
void tree(float x,float y,float s,float a);
void fern(float x,float y,float s,float a);
void spiral(int x,int y,float r,float a);
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3);
void drawSquare(int x,int y,float s);
int main()
{
	int width = 700, height = 700;
	float mrgn, size, r, angle;
 	char c= 0; 
	bool loop= true;
  gfx_open(width, height, "Fractals");
  while(loop) {
	c= gfx_wait();  // accept user input
    gfx_clear();    
	switch (c) {  // performance varies depending upon user input
		case '1':    // Sierpinski triangles
		  mrgn= 20;
		  sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
		  break; 
		case '2':    // Shrinking squares
		  mrgn= width/2;
		  shrink(width/2,height/2,mrgn);
		  break;
		case '3':   // Spiraling squares
		  r=3;
		  size=2.;
		  angle=0.0;
		  squareSpiral(width/2,height/2,r,size,angle);
		  break;
		case '4':  // Circular lace
		  r=200;
		  lace(width/2,height/2,r);
		  break;
		case '5':  // Snowflake
		  size= width/3;
		  snowflake(width/2,height/2,size);
		  break;
		case '6':  // Tree
		  angle= (M_PI)/2.;
		  size=0.6*height/2;
		  tree(width/2,height,size,angle);
		  break;
		case '7':   // Fern
		  angle= (M_PI/2.);
		  size= 0.6*height;
		  fern(width/2.,height,size,angle);
		  break;
		case '8':     // Spiral
		 angle=(M_PI/2.);
		 r= width;
		 spiral(width/2,height/2,r,angle);
		 break;
		case 'q':
		  loop= false;  // end loop
		  break;
		default:
		  break;
	}
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

void shrink(int x, int y, float s)
{
	// Base case
	if (s<2) return;

	// Draw the square
	drawSquare(x,y,s);

	// Recursive calls
	// For each new square drawn, draw four squares, each centered at one of its vertices
	shrink(x-s/2,y+s/2, s/2.2);
	shrink(x+s/2,y+s/2,s/2.2);
	shrink(x+s/2,y-s/2,s/2.2);
	shrink(x-s/2,y-s/2,s/2.2);
}

void squareSpiral(int x, int y, float r, float s, float a) 
{
	// Base case
	if ( r >400 ) return;

	// Draw the square
	drawSquare(x+r*cos(a),y-r*sin(a),s);


	a+= (M_PI/180.)*36;

	// Recursive calls
	// For each new square drawn, draw another square of a greater size and rotated about the center of the preceding square
	squareSpiral(x,y,1.1*r,1.08*s,a);
}

void lace(int x, int y, float r) {
	float angle= 0.0;

	// Base Case
	if (r<1) return;


	// Draw the circle
	gfx_circle(x,y,r);

	// Recursive calls
	// For each new circle drawn, draw 6 circles orbiting its circumference
	while(angle <= 2*M_PI) {
		lace(x+r*cos(angle),y+r*sin(angle),r/3);
		angle += (M_PI/180.)*60.;   // increment angle so as to draw a circle six times
	}
}

void snowflake(float x,float y, float s) {
	float angle= 3.*(M_PI/2.);

	// Base case
	if (s<1) return;

	while(angle <= 7.*(M_PI/2.)) {
		// Draw the line
		gfx_line(x,y,x+s*cos(angle),y+s*sin(angle));

		// Recursive calls
		// For each new line drawn, draw another line at an angle to the given line
		snowflake(x+s*cos(angle),y+s*sin(angle),s/3);

		angle += (M_PI/180.) * 72.;
	}
}

void tree(float x, float y, float s, float a) {
	// Base case
	if (s<1) return;

	// Draw the line
	gfx_line(x,y,x+s*cos(a),y-s*sin(a));

	// Recursive calls
	// For each line drawn, draw two lines of equal length at different angles to the given line
	tree(x+s*cos(a),y-s*sin(a),0.6*s,a+(M_PI/6.));
	tree(x+s*cos(a),y-s*sin(a),0.6*s,a-(M_PI/6.));
}

void fern(float x,float y, float s, float a) {
	// Base case
	if (s<2) return;

	// Draw the line
	gfx_line(x,y,x+s*cos(a),y-s*sin(a));

	// Recursive calls
	// For each line drawn, draw 4 pairs of lines of equal length at different angles to the given line
	for(int i=1; i<=4; i++) {
		fern(x+(s/4)*i*cos(a),y-(s/4)*i*sin(a),s/2.8,a+(M_PI/5));
		fern(x+(s/4)*i*cos(a),y-(s/4)*i*sin(a),s/2.8,a-(M_PI/5));
	}
}

void spiral(int x, int y, float r, float a) {
	float mod= 0.875;      // modifier of r value
	float a2= (M_PI)/5.;   // second angle

	// Base case
	if( r<=1 ) return;

	// Draw at point
	gfx_point(x+r*cos(a),y+r*sin(a));

	// Recursive calls
	// For each point highlighted, highlight two more points at angles to the given point
	spiral(x,y,r*mod,a+a2);
	spiral(x+r*cos(a),y+r*sin(a),r*0.4,a+a2);
}


void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}

void drawSquare(int x, int y, float s) 
{
	gfx_line(x-s/2,y+s/2,x+s/2,y+s/2);
	gfx_line(x+s/2,y+s/2,x+s/2,y-s/2);
	gfx_line(x+s/2,y-s/2,x-s/2,y-s/2);
	gfx_line(x-s/2,y-s/2,x-s/2,y+s/2);
}

