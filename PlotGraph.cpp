#include "PlotGraph.h"

#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QDebug>

PlotGraph::PlotGraph(qreal sizeW, qreal sizeH, qreal startingPoint, QWidget *parent)
    :QGraphicsScene(parent)
{
    this->setItemIndexMethod(QGraphicsScene::NoIndex);
    sceneX = -sizeW/2 - 5;
    sceneY = -sizeH/2 - 5;
    sceneWidth = sizeW - 10;
    sceneHeigth = sizeH - 10;

    this->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeigth);

    xOrigin = sceneX + 10;
    yOrigin = sceneY + sceneHeigth - 20;
    xMax = sceneX + sceneWidth - 10;
    yMax = sceneY + 10;

    qDebug() << "xo:  " << xOrigin << "  yo  " << yOrigin << "  xmax  " << xMax << "  ymax  " << yMax;

    addingLine = 0;
    oldPoint = startingPoint;
}



void PlotGraph::updatePoint(double newPoint)
{
    //qDebug() << "Timer ID:" << event->timerId();

    //ATENCAO - y e invertido

    addingLine++;
    qreal xStep = 1;
    qreal y1a = oldPoint;
    qreal y1b = newPoint;
    this->addLine(xOrigin + (-1 + addingLine) * xStep,
                  yOrigin - y1a,
                  xOrigin + addingLine * xStep,
                  yOrigin - y1b,
                  QPen(Qt::blue, 2));

    oldPoint = newPoint;
}

void PlotGraph::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::white);
    painter->setOpacity(0.7);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    painter->setPen(QPen(Qt::black, 3));
    painter->drawLine(
                QPointF(sceneX + 10, sceneY + 10),
                QPointF(sceneX + 10, sceneY + sceneHeigth - 10));
    painter->drawLine(
                QPointF(sceneX + 5, sceneY + sceneHeigth - 20),
                QPointF(sceneX + sceneWidth - 10, sceneY + sceneHeigth - 20));

    //legenda
    painter->setPen(QPen(Qt::blue, 3));
    painter->drawEllipse(QPointF(sceneX+20,sceneY+30),5,5);
    QGraphicsTextItem *text1 = this->addText("Alimento"); //fredmudar
    text1->setPos(sceneX+30,sceneY+20);
}

double PlotGraph::maxValue(std::vector<double> & x)
{
    int iMax = 0;
    double max = x[iMax];
    for(size_t i = 1; i < x.size(); i++)
    {
        if(x[i] > max)
        {
            iMax = i;
            max = x[i];
        }
    }
    return max;
}
