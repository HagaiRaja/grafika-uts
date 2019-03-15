#include "render.h"

#define TOOLBARS_ASSET "asset/toolbar.txt"
#define ATTRIBUTE_ASSET "asset/attribute.txt"
#define FILE_ASSET "asset/file.txt"
#define OBJECT_ASSET "asset/object.txt"
#define VIEW_ASSET "asset/view.txt"

#include <fstream>

using namespace std;

Screen PaintScreen;
extern Pane toolbars, file, attribute, object, view, canvas;

// Airplane* airplane = new Airplane(top, white, -1);
extern point mousePosition;
extern int activeToolbarIndex;
int edgeX, edgeY;
color white = {255, 255, 255, 0};
color black = {0, 0, 0, 0};
Pointer* pointer = new Pointer(mousePosition, black, 0, 0);

void loadAsset(string FILENAME, Pane& OBJECT) {
    ifstream imageFile;

    imageFile.open(FILENAME, ios::in);
    if (imageFile.is_open()) {
        imageFile >> OBJECT.width >> OBJECT.height;
        int temp_r = 0, temp_g = 0, temp_b = 0;
        for (int i = 0; i < SCREEN_HEIGHT && i < OBJECT.height; ++i) {
            for (int j = 0; j < SCREEN_WIDTH && j < OBJECT.width; ++j) {
                imageFile >> temp_r >> temp_g >> temp_b;
                OBJECT.colours[j][i].r = (unsigned char) temp_r;
                OBJECT.colours[j][i].g = (unsigned char) temp_g;
                OBJECT.colours[j][i].b = (unsigned char) temp_b;
//                draw_dot((unsigned short) j, (unsigned short) i, &temp);
            }
        }
        imageFile.close();
    } else cout << "Unable to open " << FILENAME << " file";

}

// loading picture to buffer and display paint default window
void initPaint() {
    init();

    // setting up background color to black
    set_background(&black);

    // setting default canvas size and colour
    canvas.width = CANVAS_INIT_WIDTH; canvas.height = CANVAS_INIT_HEIGHT;
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            canvas.colours[j][i] = white;
        }
    }

    // load assets
    loadAsset(TOOLBARS_ASSET, toolbars);
    loadAsset(ATTRIBUTE_ASSET, attribute);
    loadAsset(FILE_ASSET, file);
    loadAsset(OBJECT_ASSET, object);
    loadAsset(VIEW_ASSET, view);
}

// refresh the screen after changes caused by event
void refresh() {
    drawBackground();
    drawCanvas();
    drawToolbar();
    drawCursor();
}

// load the cursor (top-left is (0,0)
void drawCursor() {
    drawPicture(pointer->getDrawPoint(), mousePosition, pointer->getColor());
}

// load the toolbar and screen
void drawToolbar() {
    // Draw Toolbar
    for (int i = 0; i < SCREEN_HEIGHT && i < toolbars.height; ++i) {
        for (int j = 0; j < SCREEN_WIDTH && j < toolbars.width; ++j) {
            draw_dot((unsigned short) j, (unsigned short) i, &(toolbars.colours[j][i]));
        }
    }

    // If Clicked
    // Draw File Menu
    if (activeToolbarIndex == 1) {
        for (int i = 0; i < SCREEN_HEIGHT && i < file.height; ++i) {
            for (int j = 0; j < SCREEN_WIDTH && j < file.width; ++j) {
                draw_dot((unsigned short) j, (unsigned short) i+53, &(file.colours[j][i]));
            }
        }
    }
    // Draw Attribute Menu
    else if (activeToolbarIndex == 3) {
        for (int i = 0; i < SCREEN_HEIGHT && i < attribute.height; ++i) {
            for (int j = 0; j < SCREEN_WIDTH && j < attribute.width; ++j) {
                draw_dot((unsigned short) j + 322, (unsigned short) i+53, &(attribute.colours[j][i]));
            }
        }
    }
    // Draw Object Menu
    else if (activeToolbarIndex == 4) {
        for (int i = 0; i < SCREEN_HEIGHT && i < object.height; ++i) {
            for (int j = 0; j < SCREEN_WIDTH && j < object.width; ++j) {
                draw_dot((unsigned short) j + 535, (unsigned short) i+53, &(object.colours[j][i]));
            }
        }
    }
    // Draw View Menu
    else if (activeToolbarIndex == 2) {
        for (int i = 0; i < SCREEN_HEIGHT && i < view.height; ++i) {
            for (int j = 0; j < SCREEN_WIDTH && j < view.width; ++j) {
                draw_dot((unsigned short) j + 161, (unsigned short) i+53, &(view.colours[j][i]));
            }
        }
    }
}

// load the canvas
void drawCanvas() {
    // initiating
    if (canvas.height > SCREEN_HEIGHT) {
        edgeY = SCREEN_HEIGHT;
    }
    else {
        edgeY = canvas.height;
    }

    if (canvas.width > SCREEN_WIDTH) {
        edgeX = SCREEN_WIDTH;
    }
    else {
        edgeX = canvas.width;
    }

    // Drawing the White Canvas
    for (int i = 0; i < edgeY; ++i) {
        for (int j = 0; j < edgeX; ++j) {
            draw_dot((unsigned short) j, (unsigned short) i + 57, &(canvas.colours[j][i]));
        }
    }

    // Drawing horizontal Scale Box
    color hSide = {0,0,0, HORIZONTAL_COLOR};
    for (int j = 0; j < edgeX; ++j) {
        draw_dot((unsigned short) j, (unsigned short) OFF_SET_FROM_TOOLBAR + edgeY, &hSide);
        draw_dot((unsigned short) j, (unsigned short) OFF_SET_FROM_TOOLBAR + 1 + edgeY, &hSide);
        draw_dot((unsigned short) j, (unsigned short) OFF_SET_FROM_TOOLBAR+ 2 + edgeY, &hSide);
    }

    // Drawing vertival Scale Box
    color vSide = {0,0,0, VERTICAL_COLOR};
    for (int j = 0; j < edgeY; ++j) {
        draw_dot((unsigned short) edgeX, (unsigned short) + j + OFF_SET_FROM_TOOLBAR, &vSide);
        draw_dot((unsigned short) edgeX + 1, (unsigned short) + j + OFF_SET_FROM_TOOLBAR, &vSide);
        draw_dot((unsigned short) edgeX + 2, (unsigned short) + j + OFF_SET_FROM_TOOLBAR, &vSide);
    }

    color corner = {255,0,0, CORNER_COLOR};
    // Drawing corner Scale Box
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            draw_dot((unsigned short) edgeX + i, (unsigned short) edgeY + j + OFF_SET_FROM_TOOLBAR, &corner);
        }
    }
}

void drawBackground() {
    color c = {217,217,217, 0};
    // setting up background color to brown
    set_background(&c);
}