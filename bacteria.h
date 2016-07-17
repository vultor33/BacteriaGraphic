#ifndef BACTERIA_H
#define BACTERIA_H

#include <QGraphicsItem>
#include <QPainter>

class bacteria : public QGraphicsItem
{
public:
    bacteria();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void setDeadAlive(bool alive) { isAlive = alive; }
    bool getDeadAlive() { return isAlive; }

private:
    bool isAlive;
    qreal x,y,size;

};

#endif // BACTERIA_H
