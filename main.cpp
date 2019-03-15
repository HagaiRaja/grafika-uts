#include "paint/command.h"
#include "paint/render.h"
#include "paint/canvas.h"
#include <future>           // std::async, std::future
#include <list>

using namespace std;

bool running;
point mousePosition = {0,0};
int activeToolbarIndex = 0;
int activeMenuIndex = 0;
Pane toolbars, file, attribute, object, view, canvas;
void readMouse(int Z);
void readKeyboard(int Z);
bool event, mousePressed, scaleBoxClicked;
list<point> mouseClickHistory;

int now_command = DRAW_LINE;
color now_color = {0,0,0,0};

int main() {
    running = true;
    mouseClickHistory.clear();
    initPaint();

    // launching thread
    thread threadMouse(readMouse, 1);
    thread threadKeyboard(readKeyboard, 1);

    // reading input, press x to close
    while (running) {
        // do drawing here
        event = false;
        refresh();
        while (!event) {

        }
    }

    threadMouse.join();
    threadKeyboard.join();

    close_buffer_without_read();

    return 0;
}

// For mouse input
// change filename to your own system settings
void readMouse(int Z) {
    int fd = open("/dev/input/event16", O_RDONLY);
    struct input_event ev;
    while (running) {
        read(fd, &ev, sizeof(struct input_event));

        // Read Mouse Movement
        if(ev.type == 2) {
            event = true;
            if (ev.code == 0) {
                mousePosition.x += (double) ev.value;
                if (mousePosition.x < 0) {
                    mousePosition.x = 0;
                }
                else if (mousePosition.x > SCREEN_WIDTH) {
                    mousePosition.x = SCREEN_WIDTH;
                }
            }
            else if (ev.code == 1) {
                mousePosition.y += (double) ev.value;
                if (mousePosition.y < 0) {
                    mousePosition.y = 0;
                }
                else if (mousePosition.y > SCREEN_HEIGHT) {
                    mousePosition.y = SCREEN_HEIGHT;
                }
            }
        }
        // Read Mouse Clicks
        else if (ev.type == 1) {
            // color temp = getPixelColor((unsigned short) mousePosition.x, (unsigned short) mousePosition.y);
            cout << mousePosition.x << " " << mousePosition.y << endl;
            // cout << temp.r << " " << temp.g << " " << temp.b << " " << temp.a << endl;
            if (ev.code == 272 && ev.value == 1) {
                checkToolbar(ev);
                point temp = {mousePosition.x, mousePosition.y};
                if (checkInCanvas(temp)) {
                    mouseClickHistory.push_back(temp);
                }
                drawCommand();
//                thread mouseScaleUpdate(checkScale, ev);
            
                refresh();
                mousePressed = true;
            }
            else if (ev.code == 272 && ev.value == 0) {
                mousePressed = false;
            }
            checkToolbar(ev);
            checkScale(ev);
        }
    }

    cout << "bye from mouse" << endl;
}

// For keyboard input read
// change filename to your own system settings
void readKeyboard(int Z) {
    int fd = open("/dev/input/event4", O_RDONLY);
    struct input_event ev;
    while (running) {
        read(fd, &ev, sizeof(struct input_event));

        if(ev.type == 1) {
            event = true;
            // exitting
//           
            //Setting file menu status if corresponding button pressed
            if (ev.code == 2 && ev.value == 1) {
//                cout << mousePosition.x << " " << mousePosition.y << endl;
                if (activeToolbarIndex == 1) {
                    activeToolbarIndex = 0;
                } else {
                    activeToolbarIndex = 1;
                }
            }
            //Setting view menu status if corresponding button pressed
            else if (ev.code == 3 && ev.value == 1) {
                if (activeToolbarIndex == 2) {
                    activeToolbarIndex = 0;
                }
                else {
                    activeToolbarIndex = 2;
                }
            }
            //Setting attribute menu status if corresponding button pressed
            else if (ev.code == 4 && ev.value == 1) {
                if (activeToolbarIndex == 3) {
                    activeToolbarIndex = 0;
                }
                else {
                    activeToolbarIndex = 3;
                }
            }
            //Setting object menu status if corresponding button pressed
            else if (ev.code == 5 && ev.value == 1) {
                if (activeToolbarIndex == 4) {
                    activeToolbarIndex = 0;
                }
                else {
                    activeToolbarIndex = 4;
                }
            }
            else if (ev.code == 17 && ev.value == 1) { // W
                canvas.height -= 5;
            }
            else if (ev.code == 30 && ev.value == 1) { // A
                canvas.width -= 5;
            }
            else if (ev.code == 31 && ev.value == 1) { // S
                canvas.height += 5;
            }
            else if (ev.code == 32 && ev.value == 1) { // D
                canvas.width += 5;
            }
            else if (ev.code == 18 && ev.value == 1) { // E
                now_command = DRAW_LINE;
            }
            else if (ev.code == 19 && ev.value == 1) { // R
                now_command = DRAW_TRIANGLE;
            }
            else if (ev.code == 20 && ev.value == 1) { // T
                now_command = DRAW_RECTANGLE;
            }
            else if (ev.code == 21 && ev.value == 1) { // Y
                now_command = PAINT_BUCKET;
            }
            else if (ev.code == 22 && ev.value == 1) { // U
//                now_command = 5;
            }
            else if (ev.code == 23 && ev.value == 1) { // I
                save();
            }
            else if (ev.code == 24 && ev.value == 1) { // O
                load();
            }
            else if (ev.code == 45) {
//                printf("Bye\n");
                running = false;
            }
        }
        refresh();
    }

    cout << "bye from keyboard" << endl;
}