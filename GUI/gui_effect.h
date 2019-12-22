#ifndef EFFECTGUI_H
#define EFFECTGUI_H

#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
class Port;
class Effect;
class GUI_line;
class GUI_port;
class QGraphicsScene;
QT_END_NAMESPACE

class GUI_effect : public QGraphicsItem
{
public:
    GUI_effect(QString name, QPointF pos);
    void drag(QPointF d);

private:
    QPointF pos;
    QRectF baseRect;
    QString title;

    bool hover = false;
    QPen* pen_normal;
    QPen* pen_highlight;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

};

#endif // EFFECTGUI_H
