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

            start = getPositionOnCanvas(start);
            end = getPositionOnCanvas(end);
            drawLineOnCanvas(start, end, now_color);
        }
    }
    else if (now_command == DRAW_TRIANGLE) {
        if (mouseClickHistory.size() == 3) {
            point start = mouseClickHistory.front();
            mouseClickHistory.pop_front();
            point mid = mouseClickHistory.front();
            mouseClickHistory.pop_front();
            point end = mouseClickHistory.front();
            mouseClickHistory.pop_front();

            start = getPositionOnCanvas(start);
            mid = getPositionOnCanvas(mid);
            end = getPositionOnCanvas(end);
            drawLineOnCanvas(start, end, now_color);
            drawLineOnCanvas(mid, end, now_color);
            drawLineOnCanvas(start, mid, now_color);
        }
    }
    else if (now_command == DRAW_RECTANGLE) {
        if (mouseClickHistory.size() == 2) {
            point start = mouseClickHistory.front();
            mouseClickHistory.pop_front();
            point end = mouseClickHistory.front();
            mouseClickHistory.pop_front();

            start = getPositionOnCanvas(start);
            end = getPositionOnCanvas(end);

            point
                topLeft =  {start.x, start.y},
                topRight = {start.x, end.y},
                bottomLeft = {end.x, end.y},
                bottomRight = {end.x, start.y};
            drawLineOnCanvas(topLeft, topRight, now_color);
            drawLineOnCanvas(topRight, bottomLeft, now_color);
            drawLineOnCanvas(bottomLeft, bottomRight, now_color);
            drawLineOnCanvas(bottomRight, topLeft, now_color);
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
        // Scale Box Clicked
    else if (mousePosition.x >= edgeX && mousePosition.x < edgeX + 7 && mousePosition.y > edgeY + OFF_SET_FROM_TOOLBAR && mousePosition.y < edgeY + 7 + OFF_SET_FROM_TOOLBAR) {

        scaleBoxClicked = true;
    }
    else {
        activeToolbarIndex = 0;
    }
}

void checkScale(input_event ev) {
    // Canvas Scale Corner click
    if (!mousePressed && scaleBoxClicked) {
        scaleBoxClicked = false;
        canvas.width = mousePosition.x;
        canvas.height = mousePosition.y;
    }
}
