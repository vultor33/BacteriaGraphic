#include "PlotGraph.h"

#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QDebug>
#include <string>
#include <sstream>

PlotGraph::~PlotGraph()
{
//    delete pointsScaleLabel;
}

PlotGraph::PlotGraph(qreal sizeW, qreal sizeH, qreal startingPoint, qreal pointsScale_in, QString title, QWidget *parent)
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

    addingLine = 0;
    oldPoint = startingPoint;

    //legenda
    QGraphicsTextItem *text1 = this->addText(title);
    text1->setPos(-20 + xOrigin + (xMax - xOrigin)/2,yMax - 5);

    //pointsScale = (yOrigin-yMax)/2;
    pointsScale = pointsScale_in;
//    QString yMed = QString::number(pointsScale);
//    QGraphicsTextItem *pScale = this->addText(yMed);
//    pointsScaleLabel = pScale;
//    pointsScaleLabel->setPos(xOrigin - 25,yMax + (yOrigin - yMax)/2);
    this->addLine(xOrigin - 3, yMax + (yOrigin-yMax)/2 + 10, xOrigin + 3, yMax + (yOrigin-yMax)/2 + 10,QPen(Qt::black, 4));
}


void PlotGraph::updatePoint(double newPoint)
{
    // observar a variacao do y e o maximo

    //ATENCAO - y e invertido
    qreal xStep = 1;
    addingLine++;
    if((xOrigin + addingLine * xStep) < xMax)
    {
        qreal yStep = ((yOrigin-yMax)/2) / pointsScale;
        qreal y1a = oldPoint;
        qreal y1b = newPoint;
        this->addLine(xOrigin + (-1 + addingLine) * xStep,
                    yOrigin - y1a * yStep,
                    xOrigin + addingLine * xStep,
                    yOrigin - y1b * yStep,
                    QPen(Qt::blue, 2));
        oldPoint = newPoint;
    }
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
                QPointF(xOrigin, yMax),
                QPointF(xOrigin, yOrigin + 10));
    painter->drawLine(
                QPointF(xOrigin - 5, yOrigin),
                QPointF(xMax, yOrigin));

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
