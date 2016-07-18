#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>


class PlotGraph : public QGraphicsScene
{
    Q_OBJECT

public:
    PlotGraph(qreal sizeW, qreal sizeH, qreal startingPoint, QWidget *parent = 0);

    void updatePoint(double newPoint);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

private:
    int sceneX;
    int sceneY;
    int sceneHeigth;
    int sceneWidth;

    int xOrigin;
    int yOrigin;
    int xMax;
    int yMax;

    qreal oldPoint;
    int addingLine;

    double maxValue(std::vector<double> & x);

};

#endif // PLOTGRAPH_H
