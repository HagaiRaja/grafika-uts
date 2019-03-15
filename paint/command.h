/* ********** Definition of function for paint event function ********** */

#ifndef INPUT_H
#define INPUT_H

#include "render.h"
#include <iostream>
#include <thread>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>


// void save();
// ...

void checkToolbar(input_event ev);
void checkScale(input_event ev);

#endif