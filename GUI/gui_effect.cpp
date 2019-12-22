#include "gui_effect.h"

#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>

#include "gui_port.h"
#include "gui_line.h"
#include "ports/port.h"

GUI_effect::GUI_effect(QString name, QPointF pos) : QGraphicsItem()
{
    setData(0,"effect");
    this->pos = pos;
    baseRect = QRectF(-200,-200,200,200);
    title = name;

    setAcceptHoverEvents(true);

    pen_normal = new QPen(QColor(0,0,0));
    pen_highlight = new QPen(QColor(100,100,255,150),2);
}


QRectF GUI_effect::boundingRect() const
{
    return baseRect;
}

void GUI_effect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QColor(0,0,0));

    //Set up title properly with boundingrect and font
    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);
    
    if (hover){
        painter->setPen(*pen_highlight);
        painter->drawRect(QRectF(baseRect.topLeft()-QPoint(5,5), baseRect.bottomRight()+QPoint(5,5)));
    }

    painter->setPen(*pen_normal);
    painter->drawRect(baseRect);
    painter->drawText(QPointF(baseRect.topLeft().x()+10, baseRect.topLeft().y()+10), title);
}

void GUI_effect::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    hover = true;
}

void GUI_effect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    hover = false;
}

