#include "render.h"

#define TOOLBARS_ASSET "asset/main.txt"
#define ATTRIBUTE_ASSET "asset/attribute.txt"
#define FILE_ASSET "asset/file.txt"
#define OBJECT_ASSET "asset/object.txt"
#define VIEW_ASSET "asset/view.txt"

#include <fstream>

using namespace std;

Screen PaintScreen;
Pane toolbars, file, attribute, object, view;

// Airplane* airplane = new Airplane(top, white, -1);
extern point mousePosition;
extern int activeToolbarIndex;
extern point canvasSize;
color white = {255, 255, 255, 0};
color black = {0, 0, 0, 0};
Pointer* pointer = new Pointer(mousePosition, white, 0, 0);

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

    // load assets
    loadAsset(TOOLBARS_ASSET, toolbars);
    loadAsset(ATTRIBUTE_ASSET, attribute);
    loadAsset(FILE_ASSET, file);
    loadAsset(OBJECT_ASSET, object);
    loadAsset(VIEW_ASSET, view);
}

// refresh the screen after changes caused by event
void refresh() {
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
    for (int i = 0; i < SCREEN_HEIGHT && i < toolbars.height; ++i) {
        for (int j = 0; j < SCREEN_WIDTH && j < toolbars.width; ++j) {
            draw_dot((unsigned short) j, (unsigned short) i, &(toolbars.colours[j][i]));
        }
    }

    if (activeToolbarIndex == 1) {
        for (int i = 0; i < SCREEN_HEIGHT && i < file.height; ++i) {
            for (int j = 0; j < SCREEN_WIDTH && j < file.width; ++j) {
                draw_dot((unsigned short) j, (unsigned short) i+53, &(file.colours[j][i]));
            }
        }
    }

    else if (activeToolbarIndex == 3) {
        for (int i = 0; i < SCREEN_HEIGHT && i < attribute.height; ++i) {
            for (int j = 0; j < SCREEN_WIDTH && j < attribute.width; ++j) {
                draw_dot((unsigned short) j + 322, (unsigned short) i+53, &(attribute.colours[j][i]));
            }
        }
    }

    else if (activeToolbarIndex == 4) {
        for (int i = 0; i < SCREEN_HEIGHT && i < object.height; ++i) {
            for (int j = 0; j < SCREEN_WIDTH && j < object.width; ++j) {
                draw_dot((unsigned short) j + 535, (unsigned short) i+53, &(object.colours[j][i]));
            }
        }
    }

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
    for (int i = 0; i < SCREEN_HEIGHT && i < canvasSize.y; ++i) {
        for (int j = 0; j < SCREEN_WIDTH && j < canvasSize.x; ++j) {
            draw_dot((unsigned short) j + 14, (unsigned short) i + 67, &white);
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT && i < 10; ++i) {
        for (int j = 0; j < SCREEN_WIDTH && j < 10; ++j) {
            draw_dot((unsigned short) j + canvasSize.y + 9, (unsigned short) i + canvasSize.x + 62, &black);
        }
    }
}