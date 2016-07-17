#ifndef BACTERIAANIMATION_H
#define BACTERIAANIMATION_H

#include <QGraphicsView>
#include <QList>
#include <vector>

#include "bacteria.h"

class bacteriaanimation : public QGraphicsScene
{
    Q_OBJECT

public:
    bacteriaanimation(qreal animW, qreal animH, QWidget *parent = 0);

    void bacteriaUpdate(std::vector<bool> & alive);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    int timerId;
    int timerAnimation;
    QList<bacteria *> allBacterias;

    bacteria * bact1;
    std::vector< std::vector<int> > bacteriaGrid;

    int sceneX;
    int sceneY;
    int sceneHeigth;
    int sceneWidth;
    qreal bacHorizonSize;
    qreal bacVertSize;
    int nHorizon;
    int nVert;

    void findSlotToReplicate(int & x, int & y);
    QPointF findGridPosition(int iBac);
    double randcpp(double fMin, double fMax);
    int randcpp(int fMin, int fMax);

};

#endif // BACTERIAANIMATION_H
