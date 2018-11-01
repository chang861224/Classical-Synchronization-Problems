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

}

void
Canvas::drawSingleLaneBridge()
{
    _solidLines.clear();
    _dottedLines.clear();
    const int laneWidth = 100;

    _dottedLines.push_back(Line(0, height/2, width/4, height/2));
    _solidLines.push_back(Line(0, (height/2)+laneWidth, width/4, (height/2)+laneWidth));
    _solidLines.push_back(Line(0, (height/2)-laneWidth, width/4, (height/2)-laneWidth));
    _solidLines.push_back(Line(width/4, (height/2)+laneWidth, width/3, (height/2)+(laneWidth/2)));
    _solidLines.push_back(Line(width/4, (height/2)-laneWidth, width/3, (height/2)-(laneWidth/2)));
    _solidLines.push_back(Line(width/3, (height/2)+(laneWidth/2), width*2/3, (height/2)+(laneWidth/2)));
    _solidLines.push_back(Line(width/3, (height/2)-(laneWidth/2), width*2/3, (height/2)-(laneWidth/2)));
    _solidLines.push_back(Line(width*2/3, (height/2)+(laneWidth/2), width*3/4, (height/2)+(laneWidth)));
    _solidLines.push_back(Line(width*2/3, (height/2)-(laneWidth/2), width*3/4, (height/2)-(laneWidth)));
    _dottedLines.push_back(Line(width*3/4, height/2, width, height/2));
    _solidLines.push_back(Line(width*3/4, (height/2)+laneWidth, width, (height/2)+laneWidth));
    _solidLines.push_back(Line(width*3/4, (height/2)-laneWidth, width, (height/2)-laneWidth));

}
