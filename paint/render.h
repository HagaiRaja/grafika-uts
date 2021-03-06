/* ********** Definition of function for paint rendering ********** */

#ifndef RENDER_H
#define RENDER_H


#include "../graphics/draw.hpp"
#include "../object/pointer/pointer.h"
#include <iostream>
#include <list>
#include <math.h>
#include <string>
using namespace std;


#define CORNER_COLOR 52
#define  HORIZONTAL_COLOR 51
#define  VERTICAL_COLOR 50
#define OFF_SET_FROM_TOOLBAR 57
#define CANVAS_INIT_WIDTH 800
#define CANVAS_INIT_HEIGHT 500

typedef struct{
    color colours[SCREEN_WIDTH][SCREEN_HEIGHT];        // define all the color of the object
    int width, height;                                 // neff of the object size
} Pane;

typedef struct{
    color canvas[SCREEN_WIDTH][SCREEN_HEIGHT];         // define all the color on the canvas
    int width, height;                                 // width and height of real canvas
    bool horizontal, vertical;                         // true means left and top, false means right and bottom
} Screen;

// loading picture to buffer and display paint default window
void initPaint();

// refresh the screen after changes caused by event
void refresh();

// load the cursor (top-left is (0,0)
void drawCursor();

// load the toolbar and screen
void drawToolbar();

// load the canvas
void drawCanvas();

// load the background, change the color inside this function
void drawBackground();


#endif