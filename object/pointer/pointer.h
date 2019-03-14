#ifndef POINTER_H
#define POINTER_H

#include "../object.h"

/* A class to draw in screen */
class Pointer : public Object {
public :
	Pointer();
	Pointer(point _center, color _colour, double _dx, double _dy);

	// update position
    void update();
    // draw the object at given center
    void draw();

	/* Setter and Getter */
	double getDx() const;
	void setDx(double i);
	double getDy() const;
	void setDy(double i);

private :
	// x and y velocity of the sample object
	double dx, dy;
};

#endif
