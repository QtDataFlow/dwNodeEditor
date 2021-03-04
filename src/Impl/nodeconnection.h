#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtCore>
#include <QtWidgets>
#include <QGraphicsLineItem>
#include "nodeitem.h"
#include "nodeconnector.h"

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

class NodeConnector;

//! [0]
class NodeConnection : public QGraphicsPathItem
{
public:
    enum { Type = UserType + 666 + 0 };
	int type() const
        { return Type;}

	virtual ~NodeConnection();
    NodeConnection(NodeConnector *startConnector, NodeConnector *endConnector,
      QGraphicsItem *parent = 0, QGraphicsScene *scene = 0, bool bidirectional = true);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setColor(const QColor &color)
        { mColor = color; }
    NodeConnector *startConnector() const
        { return mStartConnector; }
    NodeConnector *endConnector() const
        { return mEndConnector; }

	void updatePosition();

	bool bidirectional();
	bool setBidirectional(bool bidirectional);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

	//returns used/created control points (eg for debug draw,...)
	void recreatePath(QPointF& controlPoint1, QPointF& controlPoint2);
    QPolygonF createArrowPoly(const QPainterPath &p, NodeConnector* conn);

private:
    NodeConnector *mStartConnector;
    NodeConnector *mEndConnector;
    QColor mColor;
    
	qreal arrowSize;
	bool mBidirectional;

	void debugPaint(QPainter *painter, QPointF& controlPoint1, QPointF& controlPoint2);


};
//! [0]

#endif
