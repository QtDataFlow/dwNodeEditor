#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <QLabel>
#include <QtCore>
#include <QtWidgets>
#include "nodeitem.h"
#include "nodeconnection.h"

//class Edge;
//class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class NodeItem;
class NodeConnection;

class NodeConnector : public QGraphicsItem
{
public:
	enum { Type = UserType + 666 + 6 };
	int type() const
        { return Type;}
	enum ConnectorType { In=1, Out=2, InOut=3 };
	ConnectorType connectorType() const
        { return mConnectorType; }
	void setConnectorType(ConnectorType c) {
		mConnectorType = c;
	}

	enum ConnectorAlignment { None=0, Left=1, Right=2, Bottom=3, Top=4 };
	ConnectorAlignment connectorAlignment() const {
		return mConnectorAlignment;
	}
	void setConnectorAlignment(ConnectorAlignment alignment) {
		mConnectorAlignment = alignment;
	}

	bool singleConnection() const { return mSingleConnection; }
	void setSingleConnection(bool singleConnection) {
		mSingleConnection = singleConnection;
	}

	bool selfConnections() const { return mSelfConnections; }
	void setSelfConnections(bool selfConnections) {
		mSelfConnections = selfConnections;
	}


    NodeConnector(NodeItem *parent, QGraphicsScene *scene, /*QLabel*/QWidget* widget, ConnectorType  con = In, const ConnectorAlignment connectorAlignment = ConnectorAlignment::Left, const bool singleConnection = false, const bool disableWidgetOnConnection = false, const int radius = 7, const bool selfConnections = false);
	virtual ~NodeConnector();
/*
    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void calculateForces();
    bool advance();
*/
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	//dw
	void updatePosition();
	//void updatePositionGeometry();
	void addConnection(NodeConnection *arrow);
	void deleteConnection(NodeConnection *arrow);
	void deleteConnections();
	void removeConnection(NodeConnection *arrow);

	void setHighlight(bool highlight);

//private:
	int mRadius;
	ConnectorType mConnectorType;
	NodeItem *parent;
	QWidget* mWidget;
	//QWidget* label;
	//bool right;
	ConnectorAlignment mConnectorAlignment;
	QList<NodeConnection *> arrows;
	QColor darkColor;
	bool highlight;
	bool mSingleConnection;
	bool mSelfConnections;
	bool mDisableWidgetOnConnection;

	//ugly, but node ctor is called after wiget is removed, but delete of connector would otherwise activate label widget
    void removeWidget();

	void update(const QRectF & rect = QRectF());

protected:
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	//void mouseOverEvent(QGraphicsSceneMouseEvent *event);
	//void enterEvent ( QEvent * event );

private:

	void debugPaint(QPainter *painter);


};

#endif
