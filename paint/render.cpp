#include "render.h"

#define TOOLBARS_ASSET "asset/main.txt"
#define ATTRIBUTE_ASSET "asset/attribute.txt"
#define FILE_ASSET "asset/file.txt"
#define OBJECT_ASSET "asset/object.txt"
#define VIEW_ASSET "asset/view.txt"

#include <fstream>

using namespace std;

Screen PaintScreen;
Object toolbars, file, attribute, object, view;

void loadAsset(string FILENAME, Object& OBJECT) {
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
    color black = {0, 0, 0, 0};
    set_background(&black);

    // load assets
    loadAsset(TOOLBARS_ASSET, toolbars);
}

// refresh the screen after changes caused by event
void refresh() {
    for (int i = 0; i < SCREEN_HEIGHT && i < toolbars.height; ++i) {
        for (int j = 0; j < SCREEN_WIDTH && j < toolbars.width; ++j) {
            draw_dot((unsigned short) j, (unsigned short) i, &(toolbars.colours[j][i]));
        }
    }
}

// load the cursor (top-left is (0,0)
void drawCursor() {

}

// load the toolbar and screen
void drawToolbar() {

}

// load the canvas
void drawCanvas() {

}