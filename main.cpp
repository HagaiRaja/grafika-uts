#include "paint/command.h"
#include "paint/render.h"

using namespace std;

bool running;
point mousePosition = {0,0};
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

//        if(ev.type == 2)
//            printf("key %i state %i\n", ev.code, ev.value);
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
            if (ev.code == 45) {
                printf("Bye\n");
                running = false;
            }
        }
    }

    cout << "bye from keyboard" << endl;
}