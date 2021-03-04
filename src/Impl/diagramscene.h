#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H
#include <QtCore>
#include <QtWidgets>
#include <QGraphicsScene>

//dw
#include "nodeitem.h"
#include "nodeconnection.h"
#include "nodeconnector.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

//dw new
class NodeItem;

//! [0]
class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem, /*//dw*/ InsertNode, InsertNode2 };

    DiagramScene(QMenu *itemMenu, QObject *parent = 0);
    QColor lineColor() const
        { return mLineColor; }
    void setLineColor(const QColor &color);

	//dw new3: moved and ugly
	QMenu *mItemMenu;

public slots:
    void setMode(Mode mode);
    //void setItemType(DiagramItem::DiagramType type);
    //void editorLostFocus(DiagramTextItem *item);

	void setDebugDraw(bool enabled = true);
	bool isDebugDraw() { return mDebugDraw; }

signals:
    //void itemInserted(DiagramItem *item);
    //void textInserted(QGraphicsTextItem *item);
	//dw
	void nodeInserted(QGraphicsItem *item);
	void nodeItemInserted(NodeItem *item);

    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

	QColor mLineColor;
	Mode mMode;
private:
    bool isItemChange(int type);

    //DiagramItem::DiagramType mItemType;
    
    bool leftButtonDown;
    QPointF startPoint;

	NodeConnection* tmpArrow;
	NodeConnector* tmpConnector;
	NodeConnector* existingConnector;
	NodeConnector* lastHighlighted;

	bool mDebugDraw;
};
//! [0]

#endif
