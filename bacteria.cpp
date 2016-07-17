#include "bacteria.h"

#include <QGraphicsItem>
#include <QList>
#include <QPainter>
#include <QPixmap>


bacteria::bacteria()
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations); // a luz nao pode rodar.
    setFlag(ItemSendsGeometryChanges); // quando o cara e movimentado voce manda um aviso
    setCacheMode(DeviceCoordinateCache);// otimiza renderizacao
    setZValue(-1);

    isAlive = true;
    x = 0;
    y = 0;
    size = 20;
}

QRectF bacteria::boundingRect() const
{
    return QRectF(
                x - 1 ,
                y - 1,
                size + 1,
                size + 1);
}

// SE NAO DEFINIR ISSO AQUI A FIGURA VIRA UM RETANGULO
// AI VOCE CLICA NO RETANGULO ELE ENTENDE QUE E NA BOLINHA.
QPainterPath bacteria::shape() const
{
    QPainterPath path;
    path.addEllipse(x, y, size, size);
    return path;
}


void bacteria::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);

   QRadialGradient gradient((int)(x/3), (int)(y/3), (int)(size/2));
   gradient.setColorAt(0, Qt::white);

   if(isAlive)
   {
       gradient.setColorAt(1, Qt::green);
       painter->setBrush(gradient);
       painter->setOpacity(0.5);
       painter->setPen(QPen(Qt::black, 0));
       painter->drawEllipse(x, y, size, size);
       painter->drawEllipse(4, 5, 5, 10);
       painter->drawEllipse(11, 5, 5, 10);
   }
   else
   {
       gradient.setColorAt(1, Qt::darkGreen);
       painter->setBrush(gradient);
       painter->setOpacity(0.5);
       painter->setPen(QPen(Qt::black, 0));
       painter->drawEllipse(x, y, size, size);
       painter->drawLine(QPointF(4,5),QPointF(9,12));
       painter->drawLine(QPointF(11,5),QPointF(16,12));
       painter->drawLine(QPointF(9,5),QPointF(4,12));
       painter->drawLine(QPointF(16,5),QPointF(11,12));
       painter->drawEllipse(8, 14, 5, 5);
   }


}
