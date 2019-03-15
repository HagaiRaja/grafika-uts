//
// Created by hagairaja on 15/03/19.
//

#include "canvas.h"

extern Pane toolbars, file, attribute, object, view, canvas;

int offsetX = 0, offsetY = OFF_SET_FROM_TOOLBAR;

// check position on canvas
bool checkInCanvas(point p) {
    if (p.x > offsetX && p.x < offsetX + canvas.width
        && p.y > offsetY && p.y < offsetY + canvas.height) {
        return true;
    }
    else {
        return false;
    }
}

// get position on canvas
point getPositionOnCanvas(point p) {
    point temp = {
        p.x - offsetX,
        p.y - offsetY
    };

    return temp;
}

// drawing a dot on positin (x,y) with given color c
void drawDotOnCanvas(unsigned short x, unsigned short y, color c) {
    if (x < SCREEN_WIDTH && x >= 0 && y < SCREEN_HEIGHT && y >= 0) {
        canvas.colours[x][y] = c;
    }
}

// return color of a pixel
color getPixelColorOnCanvas(unsigned short x, unsigned short y) {
    return canvas.colours[x][y];
}

// Drawing line from point p to point q with given color c
void drawLineOnCanvas(point p, point q, color c) {
//    cout << "woi" << endl;
    double px = p.x, py = p.y, qx = q.x, qy = q.y;
    double temp;

    if (((unsigned short) (p.x)) == ((unsigned short) (q.x))) { // infinity margin
        if (((unsigned short) (p.y)) > ((unsigned short) (q.y))) {
            for (unsigned short i = 0; i < absolute(py - qy); ++i)
            {
                /* code */
                drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y))-i, c);
            }
        }
        else {
            for (unsigned short i = 0; i < absolute(py - qy); ++i)
            {
                /* code */
                drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y))+i, c);
            }
        }
    }
    else {
        double margin = (py - qy)/(px - qx);
        if (margin > 1) {
            double newMargin = 1 / margin;
            temp = newMargin;

            drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
            if (((unsigned short) (p.y)) > ((unsigned short) (q.y))) {
                do {
                    p.y -= 1;
                    if (temp > 1) {
                        temp -= 1;
                        p.x -= 1;
                    }
                    temp += newMargin;
                    drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
                } while ((((unsigned short) (p.x)) != ((unsigned short) (q.x))) && (((unsigned) (p.y)) != ((unsigned short) (q.y))));
            }
            else {
                do {
                    p.y += 1;
                    if (temp > 1) {
                        temp -= 1;
                        p.x += 1;
                    }
                    temp += newMargin;
                    drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
                } while ((((unsigned short) (p.x)) != ((unsigned short) (q.x))) && (((unsigned) (p.y)) != ((unsigned short) (q.y))));
            }
        }
        else if (margin < -1) {
            double newMargin = 1 / margin;
            temp = newMargin;

            drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
            if (((unsigned short) (p.y)) > ((unsigned short) (q.y))) {
                do {
                    p.y -= 1;
                    if (temp < -1) {
                        temp += 1;
                        p.x += 1;
                    }
                    temp += newMargin;
                    drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
                } while ((((unsigned short) (p.x)) != ((unsigned short) (q.x))) && (((unsigned) (p.y)) != ((unsigned short) (q.y))));
            }
            else {
                do {
                    p.y += 1;
                    if (temp < -1) {
                        temp += 1;
                        p.x -= 1;
                    }
                    temp += newMargin;
                    drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
                } while ((((unsigned short) (p.x)) != ((unsigned short) (q.x))) && (((unsigned) (p.y)) != ((unsigned short) (q.y))));
            }
        }
        else if (margin == 1) {
            if (((unsigned short) (p.y)) > ((unsigned short) (q.y))) {
                for (unsigned short i = 0; i < absolute(py - qy); ++i)
                {
                    /* code */
                    drawDotOnCanvas(((unsigned short) (p.x))-i, ((unsigned short) (p.y))-i, c);
                }
            }
            else {
                for (unsigned short i = 0; i < absolute(py - qy); ++i)
                {
                    /* code */
                    drawDotOnCanvas(((unsigned short) (p.x))+i, ((unsigned short) (p.y))+i, c);
                }
            }
        }
        else if (margin == -1) {
            if (((unsigned short) (p.y)) > ((unsigned short) (q.y))) {
                for (unsigned short i = 0; i < absolute(py - qy); ++i)
                {
                    /* code */
                    drawDotOnCanvas(((unsigned short) (p.x))+i, ((unsigned short) (p.y))-i, c);
                }
            }
            else {
                for (unsigned short i = 0; i < absolute(py - qy); ++i)
                {
                    /* code */
                    drawDotOnCanvas(((unsigned short) (p.x))-i, ((unsigned short) (p.y))+i, c);
                }
            }
        }
        else if (margin > -1 && margin < 0) {
            temp = margin;

            drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
            if (((unsigned short) (p.y)) > ((unsigned short) (q.y))) {
                do {
                    p.x += 1;
                    if (temp < -1) {
                        temp += 1;
                        p.y -= 1;
                    }
                    temp += margin;
                    drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
                } while ((((unsigned short) (p.x)) != ((unsigned short) (q.x))) && (((unsigned) (p.y)) != ((unsigned short) (q.y))));
            }
            else {
                do {
                    p.x -= 1;
                    if (temp < -1) {
                        temp += 1;
                        p.y += 1;
                    }
                    temp += margin;
                    drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
                } while ((((unsigned short) (p.x)) != ((unsigned short) (q.x))) && (((unsigned) (p.y)) != ((unsigned short) (q.y))));
            }
        }
        else if (margin < 1 && margin > 0) {
            temp = margin;

            drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
            if (((unsigned short) (p.y)) > ((unsigned short) (q.y))) {
                do {
                    p.x -= 1;
                    if (temp > 1) {
                        temp -= 1;
                        p.y -= 1;
                    }
                    temp += margin;
                    drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
                } while ((((unsigned short) (p.x)) != ((unsigned short) (q.x))) && (((unsigned) (p.y)) != ((unsigned short) (q.y))));
            }
            else {
                do {
                    p.x += 1;
                    if (temp > 1) {
                        temp -= 1;
                        p.y += 1;
                    }
                    temp += margin;
                    drawDotOnCanvas(((unsigned short) (p.x)), ((unsigned short) (p.y)), c);
                } while ((((unsigned short) (p.x)) != ((unsigned short) (q.x))) && (((unsigned) (p.y)) != ((unsigned short) (q.y))));
            }
        }
        else { // margin 0
            if (((unsigned short) (p.x)) > ((unsigned short) (q.x))) {
                for (unsigned short i = 0; i < absolute(px - qx); ++i)
                {
                    /* code */
                    drawDotOnCanvas(((unsigned short) (p.x))-i, ((unsigned short) (p.y)), c);
                }
            }
            else {
                for (unsigned short i = 0; i < absolute(px - qx); ++i)
                {
                    /* code */
                    drawDotOnCanvas(((unsigned short) (p.x))+i, ((unsigned short) (p.y)), c);
                    drawDotOnCanvas(((unsigned short) (p.x))+i, ((unsigned short) (p.y)), c);
                }
            }
        }
    }
}
