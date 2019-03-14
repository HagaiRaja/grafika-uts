#include "pointer.h"

Pointer::Pointer()
{
	dx = 0;
	dy = -1;
}

Pointer::Pointer(point _center, color _colour, double _dx, double _dy) : Object (_center, _colour, "object/pointer/pointer.txt")
{
	dx = _dx;
	dy = _dy;
}


// update position
void Pointer::update()
{
	point new_center = this->getCenter();
	new_center.x += dx;
	new_center.y += dy;
	this->setCenter(new_center);
}

// draw the object at given center
void Pointer::draw()
{
	this->update();

	// draw the shape using line. On this example we draw rectangle
	drawPicture(this->getDrawPoint(), this->getCenter(), this->getColor());
}


/* Setter and Getter */
double Pointer::getDx() const
{
	return dx;
}

void Pointer::setDx(double i)
{
	dx = i;
}

double Pointer::getDy() const
{
	return dy;
}

void Pointer::setDy(double i)
{
	dy = i;
}
