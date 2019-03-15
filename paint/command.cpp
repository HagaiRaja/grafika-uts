#include "command.h"

//struct input_event {
//    struct timeval time;
//    unsigned short type;
//    unsigned short code;
//    unsigned int value;
//};

extern bool running, mousePressed, scaleBoxClicked;
extern point mousePosition;
extern int activeToolbarIndex, activeMenuIndex;
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
    else {
        checkMenu(ev);
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

void checkMenu (input_event ev) {
    if (ev.value == 1) {
        // Check per menu, ranged from 1 - 23. Numbering starts from the left and upmost menu
        if (activeToolbarIndex == 1) {
            if (mousePosition.x < 161 && mousePosition.y >= 53 && mousePosition.y < 106) {
                activeMenuIndex = 1;
            }
            else if (mousePosition.x < 161 && mousePosition.y >= 106 && mousePosition.y < 159) {
                activeMenuIndex = 2;
            }
            else if (mousePosition.x < 161 && mousePosition.y >= 159 && mousePosition.y < 212) {
                activeMenuIndex = 3;
            }
            else if (mousePosition.x < 161 && mousePosition.y >= 212 && mousePosition.y < 265) {
                activeMenuIndex = 4;
            }
        }
        else if (activeToolbarIndex == 2) {
            if (mousePosition.x >= 161 && mousePosition.x < 322 && mousePosition.y >= 53 && mousePosition.y < 106) {
                activeMenuIndex = 5;
            }
            else if (mousePosition.x >= 161 && mousePosition.x < 322 && mousePosition.y >= 106 && mousePosition.y < 159) {
                activeMenuIndex = 6;
            }
            else if (mousePosition.x >= 161 && mousePosition.x < 322 && mousePosition.y >= 159 && mousePosition.y < 212) {
                activeMenuIndex = 7;
            }
            else if (mousePosition.x >= 161 && mousePosition.x < 322 && mousePosition.y >= 212 && mousePosition.y < 265) {
                activeMenuIndex = 8;
            }
            else if (mousePosition.x >= 161 && mousePosition.x < 322 && mousePosition.y >= 265 && mousePosition.y <318) {
                activeMenuIndex = 9;
            }
            else if (mousePosition.x >= 161 && mousePosition.x < 322 && mousePosition.y >= 318 && mousePosition.y < 371) {
                activeMenuIndex = 10;
            }
            else if (mousePosition.x >= 161 && mousePosition.x < 322 && mousePosition.y >= 371 && mousePosition.y < 424) {
                activeMenuIndex = 11;
            }
        }
        else if (activeToolbarIndex == 3) {
            if (mousePosition.x >= 322 && mousePosition.x < 535 && mousePosition.y >= 53 && mousePosition.y < 106) {
                activeMenuIndex = 12;
            }
            else if (mousePosition.x >= 322 && mousePosition.x < 535 && mousePosition.y >= 106 && mousePosition.y < 159) {
                activeMenuIndex = 13;
            }
            else if (mousePosition.x >= 322 && mousePosition.x < 535 && mousePosition.y >= 159 && mousePosition.y < 212) {
                activeMenuIndex = 14;
            }
            else if (mousePosition.x >= 322 && mousePosition.x < 535 && mousePosition.y >= 212 && mousePosition.y < 265) {
                activeMenuIndex = 15;
            }
            else if (mousePosition.x >= 322 && mousePosition.x < 535 && mousePosition.y >= 265 && mousePosition.y <318) {
                activeMenuIndex = 16;
            }
            else if (mousePosition.x >= 322 && mousePosition.x < 535 && mousePosition.y >= 318 && mousePosition.y < 371) {
                activeMenuIndex = 17;
            }
            else if (mousePosition.x >= 322 && mousePosition.x < 535 && mousePosition.y >= 371 && mousePosition.y < 424) {
                activeMenuIndex = 18;
            }
        }
        else if (activeToolbarIndex == 4) {
            if (mousePosition.x >= 535 && mousePosition.x < 722 && mousePosition.y >= 53 && mousePosition.y < 106) {
                activeMenuIndex = 19;
            }
            else if (mousePosition.x >= 535 && mousePosition.x < 722 && mousePosition.y >= 106 && mousePosition.y < 159) {
                activeMenuIndex = 20;
            }
            else if (mousePosition.x >= 535 && mousePosition.x < 722 && mousePosition.y >= 159 && mousePosition.y < 212) {
                activeMenuIndex = 21;
            }
            else if (mousePosition.x >= 535 && mousePosition.x < 722 && mousePosition.y >= 212 && mousePosition.y < 265) {
                activeMenuIndex = 22;
            }
            else if (mousePosition.x >= 535 && mousePosition.x < 722 && mousePosition.y >= 265 && mousePosition.y <318) {
                activeMenuIndex = 23;
            }
        }
        cout << activeMenuIndex << endl;
    }
}

// save and load
void save() {
    // open a file in write mode.
    ofstream outfile;
    outfile.open("paint.txt");

    outfile << canvas.width << " " << canvas.height << endl;
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            outfile << (int) canvas.colours[j][i].r << " " << (int) canvas.colours[j][i].g << " " <<
                    (int) canvas.colours[j][i].b << " " << (int) canvas.colours[j][i].a << endl;
        }
    }

    outfile.close();
}

void load() {
    // open a file in write mode.
    ifstream outfile;
    outfile.open("paint.txt");
    int r,g,b,a;

    outfile >> canvas.width >> canvas.height;
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            outfile >> r >> g >> b >> a;
            canvas.colours[j][i].r = (unsigned char) r;
            canvas.colours[j][i].g = (unsigned char) g;
            canvas.colours[j][i].b = (unsigned char) b;
            canvas.colours[j][i].a = (unsigned char) a;
        }
    }

    outfile.close();
}

// new canvas
void clearCanvas() {
    canvas.width = CANVAS_INIT_WIDTH;
    canvas.height = CANVAS_INIT_HEIGHT;
    color white = {255, 255, 255, 0};

    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            canvas.colours[j][i] = white;
        }
    }
}