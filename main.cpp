#include "paint/command.h"
#include "paint/render.h"

using namespace std;

bool running;
point mousePosition = {0,0};
point canvasSize = {600,600};
int activeToolbarIndex = 0;
void readMouse(int Z);
void readKeyboard(int Z);

int main() {
    running = true;
    initPaint();

    // launching thread
    thread threadMouse(readMouse, 1);
    thread threadKeyboard(readKeyboard, 1);

    // reading input, press x to close
    while (running) {
        // do drawing here
        refresh();
        usleep(30000);
    }

    threadMouse.join();
    threadKeyboard.join();

    close_buffer_without_read();

    return 0;
}

// For mouse input
// change filename to your own system settings
void readMouse(int Z) {
    int fd = open("/dev/input/event18", O_RDONLY);
    struct input_event ev;
    while (running) {
        read(fd, &ev, sizeof(struct input_event));

        if(ev.type == 2) {
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
        else if (ev.type == 1) {
            if (ev.code == 272 && ev.value == 1) {
                cout << mousePosition.x << " " << mousePosition.y << endl;
                if (mousePosition.x < 161 && mousePosition.y < 53) {
                    if (activeToolbarIndex == 1) {
                        activeToolbarIndex = 0;
                    }
                    else {
                        activeToolbarIndex = 1;
                    }
                }
                else if (mousePosition.x >= 161 && mousePosition.x < 322 && mousePosition.y < 53) {
                    if (activeToolbarIndex == 2) {
                        activeToolbarIndex = 0;
                    }
                    else {
                        activeToolbarIndex = 2;
                    }
                }
                else if (mousePosition.x >= 322 && mousePosition.x < 535 && mousePosition.y < 53) {
                    if (activeToolbarIndex == 3) {
                        activeToolbarIndex = 0;
                    }
                    else {
                        activeToolbarIndex = 3;
                    }
                }
                else if (mousePosition.x >= 535 && mousePosition.x < 722 && mousePosition.y < 53) {
                    if (activeToolbarIndex == 4) {
                        activeToolbarIndex = 0;
                    }
                    else {
                        activeToolbarIndex = 4;
                    }
                }
                else if (mousePosition.x >= canvasSize.x + 9 && mousePosition.x < canvasSize.x + 19 && mousePosition.y >= canvasSize.y + 62 && mousePosition.y < canvasSize.y + 72) {
                    while (ev.value == 1) {
                        if (ev.code == 0) {
                            canvasSize.x += (double) ev.value;
                        }
                        else if (ev.code == 1) {
                            canvasSize.y += (double) ev.value;
                        }
                    }
                }
                else {
                    activeToolbarIndex = 0;
                }
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
            // exitting
//            printf("key %i state %i\n", ev.code, ev.value);
            if (ev.code == 2 && ev.value == 1) {
//                cout << mousePosition.x << " " << mousePosition.y << endl;
                if (activeToolbarIndex == 1) {
                    activeToolbarIndex = 0;
                } else {
                    activeToolbarIndex = 1;
                }
            }
            else if (ev.code == 3 && ev.value == 1) {
                if (activeToolbarIndex == 2) {
                    activeToolbarIndex = 0;
                }
                else {
                    activeToolbarIndex = 2;
                }
            }
            else if (ev.code == 4 && ev.value == 1) {
                if (activeToolbarIndex == 3) {
                    activeToolbarIndex = 0;
                }
                else {
                    activeToolbarIndex = 3;
                }
            }
            else if (ev.code == 5 && ev.value == 1) {
                if (activeToolbarIndex == 4) {
                    activeToolbarIndex = 0;
                }
                else {
                    activeToolbarIndex = 4;
                }
            }
            else if (ev.code == 45) {
//                printf("Bye\n");
                running = false;
            }
        }
    }

    cout << "bye from keyboard" << endl;
}