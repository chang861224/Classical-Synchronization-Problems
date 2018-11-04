#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include <map>
#include "drawdatatype.h"
#include "Single-Lane-Bridge/singlelanebridge.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void drawSingleLaneBridge();

signals:

public slots:
    void updateCanvas();
    void setObjects(int id, int pos);
    void deleteObject(int id);

private:
    int width; // Canvas's width
    int height; // Canvas's height
    int carWidth;
    int carHeight;
    int upLanePos, downLanePos, midLanePos;
    const int laneWidth = 60; // Bridge's lane width
    const int lanePadding = 5;
    std::vector<Line> _solidLines;
    std::vector<Line> _dottedLines;
    std::map<int, Object> objects;

    void resizeEvent(QResizeEvent *event);
    QWidget *createCanvasWidget();
    void paintEvent(QPaintEvent *event);
};

#endif // CANVAS_H
