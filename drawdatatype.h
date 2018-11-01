#ifndef DRAWDATATYPE_H
#define DRAWDATATYPE_H

#include <QString>

struct Line
{
    Line (int x1, int y1, int x2, int y2) {
        xfrom = x1;
        yfrom = y1;
        xto = x2;
        yto = y2;
    }
    int xfrom, yfrom, xto, yto;
};

struct Object
{
    Object(int x, int y, int h, int rotate, QString path) {
        xpos = x;
        ypos = y;
        height = h;
        deg = rotate;
        imgPath = path;
    }

    int xpos, ypos, height, deg;
    QString imgPath;
};

#endif // DRAWDATATYPE_H
