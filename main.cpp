// CPP program to demonstrate multithreading
// using three different callables.
#include <iostream>
#include <thread>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "map/control.h"

using namespace std;

bool running;
//struct input_event {
//    struct timeval time;
//    unsigned short type;
//    unsigned short code;
//    unsigned int value;
//};


// For mouse input read
void readMouse(int Z) {
    int fd = open("/dev/input/event18", O_RDONLY);
    struct input_event ev;
    while (running) {
        read(fd, &ev, sizeof(struct input_event));

        if(ev.type == 2)
            printf("key %i state %i\n", ev.code, ev.value);
    }
}

// For keyboard input read
void readKeyboard(int Z) {
    int fd = open("/dev/input/event4", O_RDONLY);
    struct input_event ev;
    while (running) {
        read(fd, &ev, sizeof(struct input_event));

        if(ev.type == 1) {
            // exitting
            printf("key %i state %i\n", ev.code, ev.value);
            if (ev.code == 45) {
                printf("Bye\n");
                running = false;
            }
        }
    }
}

int main() {
    running = true;
    init();

    // launching thread
    thread threadMouse(readMouse, 1);
    thread threadKeyboard(readKeyboard, 1);

    // setting up background color to black
    color black = {0,0,0,0};
    set_background(&black);

    // reading input, press x to close
    while (running) {
        // do drawing here
    }

    // Wait for the threads to finish
    threadMouse.join();
    threadKeyboard.join();

    close_buffer_without_read();
    return 0;
}