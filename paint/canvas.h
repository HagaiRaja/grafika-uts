//
// Created by hagairaja on 15/03/19.
//

#ifndef CANVAS_H
#define CANVAS_H

#include "../graphics/draw.hpp"
#include "render.h"

// drawing a dot on positin (x,y) with given color c
void drawDotOnCanvas(unsigned short x, unsigned short y, color c);

// return color of a pixel
color getPixelColorOnCanvas(unsigned short x, unsigned short y);

// Drawing line from point p to point q with given color c
void drawLineOnCanvas(point p, point q, color c);

#endif //CANVAS_H
