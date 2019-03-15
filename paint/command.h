/* ********** Definition of function for paint event function ********** */

#ifndef INPUT_H
#define INPUT_H

#include "render.h"
#include "canvas.h"
#include <iostream>
#include <thread>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

// command list
#define DRAW_LINE 1
#define DRAW_TRIANGLE 2
#define DRAW_POLYGON 3
#define PAINT_BUCKET 4


// void save();
// ...

void checkToolbar(input_event ev);
void checkScale(input_event ev);

// calling for command
void drawCommand();

#endif