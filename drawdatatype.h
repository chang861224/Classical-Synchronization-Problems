#ifndef DRAWDATATYPE_H
#define DRAWDATATYPE_H

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

#endif // DRAWDATATYPE_H
