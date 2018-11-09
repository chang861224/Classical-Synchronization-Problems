#include "canvas.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QDebug>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    // Layout configuration
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    // Calculate car size
    carHeight = laneWidth - (lanePadding * 2);
    QPixmap tmp(":/cars/img/redcar.png");
    carWidth = carHeight * (tmp.width() / tmp.height());
}

void
Canvas::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateCanvas();
}

void
Canvas::updateCanvas()
{
    // Get widget size
    width = (this -> size()).width();
    height = (this -> size()).height();

    upLanePos = (height / 2) - laneWidth + lanePadding;
    downLanePos = (height / 2) + lanePadding;
    midLanePos = (height / 2) - (laneWidth / 2) + lanePadding;

    carHeight = laneWidth - (lanePadding * 2);
    QPixmap tmp(":/cars/img/redcar.png");
    carWidth = carHeight * (tmp.width() / tmp.height());
    emit carWidthChange(bridgeLen * carWidth / width);

    drawSingleLaneBridge();
}

QWidget*
Canvas::createCanvasWidget()
{

}

void
Canvas::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   QPen pen(QColor(139, 69, 19), 3);

   pen.setStyle(Qt::SolidLine);
   painter.setPen(pen);
   for(unsigned int iter(0); iter<_solidLines.size(); ++iter){
      Line tmp(_solidLines.at(iter));
      painter.drawLine(tmp.xfrom, tmp.yfrom, tmp.xto, tmp.yto);
   }

   pen.setStyle(Qt::DashLine);
   painter.setPen(pen);
   for(unsigned int iter(0); iter<_dottedLines.size(); ++iter){
       Line tmp(_dottedLines.at(iter));
       painter.drawLine(tmp.xfrom, tmp.yfrom, tmp.xto, tmp.yto);
   }

   std::map<int, Object>::iterator objectsIter;
   for(objectsIter=objects.begin(); objectsIter != objects.end(); ++objectsIter){
       Object tmp(objectsIter -> second);
       QPixmap img(tmp.imgPath);
       QPixmap scaledImg(img.scaledToHeight(tmp.height, Qt::SmoothTransformation));
       QTransform trans;
       QPixmap outImg(scaledImg.transformed(trans.rotate(tmp.deg)));
       painter.drawPixmap(tmp.xpos, tmp.ypos, outImg);
   }
}

void
Canvas::drawSingleLaneBridge()
{
    _solidLines.clear();
    _dottedLines.clear();

    // Line
    double turnPos[6];
    for(int iter(0); iter < 6; ++iter){
        turnPos[iter] = (double)bridgeTurnPos[iter] / bridgeLen * width;
    }
    _dottedLines.push_back(Line(turnPos[0], height/2, turnPos[1], height/2));
    _solidLines.push_back(Line(turnPos[0], (height/2)+laneWidth, turnPos[1], (height/2)+laneWidth));
    _solidLines.push_back(Line(turnPos[0], (height/2)-laneWidth, turnPos[1], (height/2)-laneWidth));
    _solidLines.push_back(Line(turnPos[1], (height/2)+laneWidth, turnPos[2], (height/2)+(laneWidth/2)));
    _solidLines.push_back(Line(turnPos[1], (height/2)-laneWidth, turnPos[2], (height/2)-(laneWidth/2)));
    _solidLines.push_back(Line(turnPos[2], (height/2)+(laneWidth/2), turnPos[3], (height/2)+(laneWidth/2)));
    _solidLines.push_back(Line(turnPos[2], (height/2)-(laneWidth/2), turnPos[3], (height/2)-(laneWidth/2)));
    _solidLines.push_back(Line(turnPos[3], (height/2)+(laneWidth/2), turnPos[4], (height/2)+(laneWidth)));
    _solidLines.push_back(Line(turnPos[3], (height/2)-(laneWidth/2), turnPos[4], (height/2)-(laneWidth)));
    _dottedLines.push_back(Line(turnPos[4], height/2, turnPos[5], height/2));
    _solidLines.push_back(Line(turnPos[4], (height/2)+laneWidth, turnPos[5], (height/2)+laneWidth));
    _solidLines.push_back(Line(turnPos[4], (height/2)-laneWidth, turnPos[5], (height/2)-laneWidth));
}

void
Canvas::setObjects(int id, int pos)
{
    bool east2west(false);
    if(pos < 0) {
        pos += bridgeLen;
        east2west = true;
    }

    // Calculate x, y position value
    int x, y;
    x = pos * width / bridgeLen;

    if(bridgeTurnPos[2] < pos && pos < bridgeTurnPos[3]) {
        y = midLanePos;
    } else if(bridgeTurnPos[1] <= pos && pos <= bridgeTurnPos[2]) {
        double ratio = (double)(pos - bridgeTurnPos[1]) / (bridgeTurnPos[2] - bridgeTurnPos[1]);
        double offset = (laneWidth / 2) * ratio;
        if(!east2west) y = upLanePos + offset;
        else y = downLanePos - offset;
    } else if(bridgeTurnPos[3] <= pos && pos <= bridgeTurnPos[4]) {
        double ratio = (double)(pos - bridgeTurnPos[3]) / (bridgeTurnPos[4] - bridgeTurnPos[3]);
        double offset = (laneWidth / 2) * ratio;
        if(!east2west) y = midLanePos - offset;
        else y = midLanePos + offset;
    } else {
        if(!east2west) y = upLanePos;
        else y = downLanePos;
    }

    if(objects.find(id) != objects.end()){
        objects.at(id).xpos = x;
        objects.at(id).ypos = y;
    } else {
        if(!east2west) objects.insert(std::pair<int, Object>(id, Object(x, y, carHeight, 0, ":/cars/img/redcar.png")));
        else {
            objects.insert(std::pair<int, Object>(id, Object(x, y, carHeight, 180, ":/cars/img/yellowcar.png")));
        }
    }
    this -> update();
}

void
Canvas::deleteObject(int id)
{
    objects.erase(id);

    this -> update();
}
