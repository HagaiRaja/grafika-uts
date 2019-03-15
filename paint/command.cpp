#include "command.h"

//struct input_event {
//    struct timeval time;
//    unsigned short type;
//    unsigned short code;
//    unsigned int value;
//};

extern bool running, mousePressed, scaleBoxClicked;
extern point mousePosition;
extern int activeToolbarIndex;
extern Pane toolbars, file, attribute, object, view, canvas;
extern int edgeX, edgeY;

void checkToolbar(input_event ev) {
    // File Menu Clicked
    if (mousePosition.x < 161 && mousePosition.y < 53) {
        if (activeToolbarIndex == 1) {
            activeToolbarIndex = 0;
        }
        else {
            activeToolbarIndex = 1;
        }
    }
        // View Menu Clicked
    else if (mousePosition.x >= 161 && mousePosition.x < 322 && mousePosition.y < 53) {
        if (activeToolbarIndex == 2) {
            activeToolbarIndex = 0;
        }
        else {
            activeToolbarIndex = 2;
        }
    }
        // Attribute Menu Clicked
    else if (mousePosition.x >= 322 && mousePosition.x < 535 && mousePosition.y < 53) {
        if (activeToolbarIndex == 3) {
            activeToolbarIndex = 0;
        }
        else {
            activeToolbarIndex = 3;
        }
    }
        // Object Menu Clicked
    else if (mousePosition.x >= 535 && mousePosition.x < 722 && mousePosition.y < 53) {
        if (activeToolbarIndex == 4) {
            activeToolbarIndex = 0;
        }
        else {
            activeToolbarIndex = 4;
        }
    }
    else {
        activeToolbarIndex = 0;
    }
}

void checkScale(input_event ev) {
    // Canvas Scale Corner click
    // Scale Box Clicked
    if (mousePosition.x >= edgeX && mousePosition.x < edgeX + 7 && mousePosition.y > edgeY + OFF_SET_FROM_TOOLBAR && mousePosition.y < edgeY + 7 + OFF_SET_FROM_TOOLBAR) {
        scaleBoxClicked = true;
    }
    if (!mousePressed && scaleBoxClicked) {
        scaleBoxClicked = false;
        canvas.width = mousePosition.x;
        canvas.height = mousePosition.y;
    }
}
