#include "command.h"

//struct input_event {
//    struct timeval time;
//    unsigned short type;
//    unsigned short code;
//    unsigned int value;
//};

extern bool running, mousePressed;
extern point mousePosition;
extern int activeToolbarIndex;
extern Pane toolbars, file, attribute, object, view, canvas;
extern int edgeX, edgeY;
extern list<point> mouseClickHistory;
extern int now_command;
extern color now_color;

// calling for command
void drawCommand() {
    if (now_command == DRAW_LINE) {
        if (mouseClickHistory.size() == 2) {
            point start = mouseClickHistory.front();
            mouseClickHistory.pop_front();
            point end = mouseClickHistory.front();
            mouseClickHistory.pop_front();
            drawLineOnCanvas(start, end, now_color);
        }
    }
//    cout << "woi" << endl;
//    drawDotOnCanvas(10 + now_command,10 + now_command, now_color);
//    now_command +=1;
}

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
    if (mousePosition.x >= edgeX && mousePosition.x < edgeX + 7 && mousePosition.y > edgeY + OFF_SET_FROM_TOOLBAR && mousePosition.y < edgeY + 7 + OFF_SET_FROM_TOOLBAR) {
        while (mousePressed) {
        }

        canvas.height = mousePosition.y;
        canvas.width = mousePosition.x;
    }
}
