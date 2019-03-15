#include "paint/command.h"
#include "paint/render.h"
#include <future>           // std::async, std::future

using namespace std;

bool running;
point mousePosition = {0,0};
int activeToolbarIndex = 0;
Pane toolbars, file, attribute, object, view, canvas;
void readMouse(int Z);
void readKeyboard(int Z);
bool event, mousePressed, scaleBoxClicked;

int main() {
    running = true;
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
    int fd = open("/dev/input/event6", O_RDONLY);
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
            if (ev.code == 0) {
                mousePressed = false;
            }
            else {
                mousePressed = true;
            }
            color temp = getPixelColor((unsigned short) mousePosition.x, (unsigned short) mousePosition.y);
//            cout << temp.r << " " << temp.g << " " << temp.b << " " << temp.a << endl;
            if (ev.code == 272 && ev.value == 1) {
                checkToolbar(ev);
//                thread mouseScaleUpdate(checkScale, ev);
            }
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
            else if (ev.code == 45) {
//                printf("Bye\n");
                running = false;
            }
        }
    }

    cout << "bye from keyboard" << endl;
}