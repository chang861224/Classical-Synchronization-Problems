#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include "drawdatatype.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void drawSingleLaneBridge();

signals:

public slots:
    void updateCanvas();

private:
    void resizeEvent(QResizeEvent *event);
    QWidget *createCanvasWidget();
    void paintEvent(QPaintEvent *event);
    std::vector<Line> _solidLines;
    std::vector<Line> _dottedLines;
    int width;
    int height;
};

#endif // CANVAS_H
