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
    Object(int x, int y, int h, QString path) {
        xpos = x;
        ypos = y;
        height = h;
        imgPath = path;
    }

    int xpos, ypos, height;
    QString imgPath;
};

#endif // DRAWDATATYPE_H
