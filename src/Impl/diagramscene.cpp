#include <QtCore>
#include <QtWidgets>

#include "diagramscene.h"
/*
#include "nodeconnection.h"
#include "nodeconnector.h"
*/

//! [0]
DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    mItemMenu = itemMenu;
    mMode = MoveItem;
    mLineColor = Qt::black;
	tmpArrow = NULL;
	tmpConnector = NULL;
	lastHighlighted = NULL;
	mDebugDraw = false;
}
//! [0]

//! [1]
void DiagramScene::setLineColor(const QColor &color)
{
    mLineColor = color;
/*    if (isItemChange(Arrow::Type)) {
        Arrow *item =
            qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item->setColor(mLineColor);
        update();
    }
	*/
}
//! [1]

void DiagramScene::setMode(Mode mode)
{
    mMode = mode;
}


/*
void DiagramScene::setItemType(DiagramItem::DiagramType type)
{
    mItemType = type;
}

//! [5]
void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}
*/
//! [5]

//! [6]
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() == Qt::LeftButton) {
		QList<QGraphicsItem *> startConnectors = items(mouseEvent->scenePos());
		foreach(QGraphicsItem * g, startConnectors) {
			if (g->type() == NodeConnector::Type) {
				NodeConnector* start = dynamic_cast<NodeConnector*>(g);
				//dw ugly
				if (start->mSingleConnection) {
					start->deleteConnections();
				}

				tmpConnector = new NodeConnector(NULL, this, NULL,NodeConnector::InOut);
				tmpConnector->setPos(mouseEvent->scenePos());
				//dw needed? addItem(tmpConnector);
				
				//dw667 backmerge: to slow if connector is child of item
				//addItem(tmpConnector);
				
				if (isDebugDraw()) {
					//debug draw
					tmpConnector->mRadius = 5;
				}
				else {
					tmpConnector->setVisible(false);
					tmpConnector->mRadius = 0;
				}


				if (start->connectorType() != NodeConnector::In) {
					tmpArrow = new NodeConnection(start, tmpConnector, NULL, this);
				}
				else {
					tmpArrow = new NodeConnection(tmpConnector, start, NULL, this);
				}
				//dw needed? addItem(tmpArrow);
				start->setHighlight(true);
				existingConnector = start;

				
				existingConnector->updatePosition();
				existingConnector->update();
				tmpConnector->updatePosition();
				tmpConnector->update();
				tmpArrow->updatePosition();
				tmpArrow->update();

				//dw667 backmerge: was commented
				//QGraphicsScene::mousePressEvent(mouseEvent);
				return;
				//addItem(tmpArrow);
				//if (
			}
		}
	}

    QGraphicsScene::mousePressEvent(mouseEvent);
}
//! [9]

//! [10]
void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (tmpArrow != 0) {

		//simple right/left handling
		if (tmpArrow->startConnector()->mapToScene(0,0).x() < tmpArrow->endConnector()->mapToScene(0,0).x()) {
			if (tmpConnector == tmpArrow->endConnector())
				tmpConnector->setConnectorAlignment(NodeConnector::ConnectorAlignment::Left);// right = false;
			else
				//tmpConnector->right = true;
				tmpConnector->setConnectorAlignment(NodeConnector::ConnectorAlignment::Right);
		}
		else {
			if (tmpConnector == tmpArrow->endConnector())
				//tmpConnector->right = true;
				tmpConnector->setConnectorAlignment(NodeConnector::ConnectorAlignment::Right);
			else
				//tmpConnector->right = false;
				tmpConnector->setConnectorAlignment(NodeConnector::ConnectorAlignment::Left);
		}

		// if we hit a connecor, highlight it and take 'right' over, switch in and out if neccessary
		QList<QGraphicsItem *> intersectedItems = items(mouseEvent->scenePos());
		while(intersectedItems.count() && (intersectedItems.first() == tmpArrow || intersectedItems.first() == tmpConnector || intersectedItems.first()->type() != NodeConnector::Type)) {
            intersectedItems.removeFirst();
		}
		if (intersectedItems.count() && intersectedItems.first() != tmpConnector && intersectedItems.first() != existingConnector) {
			//dw thats how a cast should look like
			NodeConnector *node = qgraphicsitem_cast<NodeConnector *>(intersectedItems.first());
			//ugly direction handling, only case where a switch is possible
			if (existingConnector->connectorType() == NodeConnector::InOut) {
				//switch if non matching
				if ((node->connectorType() == NodeConnector::Out && tmpArrow->startConnector() == existingConnector)
					|| (node->connectorType() == NodeConnector::In && tmpArrow->endConnector() == existingConnector)) {
					//tmpConnector->setConnectorType(node->connectorType());
					NodeConnector* old1 = tmpArrow->startConnector();
					NodeConnector* old2 = tmpArrow->endConnector();
					//dw needed? removeItem(tmpArrow);
					//dw667 backmerge: to slow if connector is child of item
					//removeItem(tmpArrow);
					delete tmpArrow;
					tmpArrow = new NodeConnection(old2, old1, NULL, this);
					//dw667 backmerge: to slow if connector is child of item
					//addItem(tmpArrow);
				}
			}
			//check if uncompatible
			else if (node->connectorType() != NodeConnector::InOut && node->connectorType() == existingConnector->connectorType()) {
				return;
			}

			node->setHighlight(true);
			/*node->updatePosition();
			node->update();*/
			//dw667 backmerge:
			node->updatePosition();
			node->update();
			
			tmpConnector->setConnectorAlignment(node->connectorAlignment());
			tmpConnector->setConnectorType(node->connectorType());
			//FIXME: make configurable
			tmpArrow->setBidirectional(true);

			tmpConnector->updatePosition();
			tmpConnector->update();
			lastHighlighted = node;
		}
		else if (lastHighlighted != NULL) {
			lastHighlighted->setHighlight(false);
			/*lastHighlighted->updatePosition();
			lastHighlighted->update();*/
			//dw667 backmerge:
			lastHighlighted->updatePosition();
			lastHighlighted->update();
			
			lastHighlighted = NULL;
			tmpConnector->updatePosition();
			tmpConnector->update();
		}

        //QLineF newLine(line->line().p1(), mouseEvent->scenePos());
		//line->setLine(newLine);
		//tmpConnector = new NodeConnector(NULL, scene, NULL, NodeConnector::InOut);
		//tmpConnector-> = new NodeConnector(NULL, scene, NULL, NodeConnector::InOut);
		tmpConnector->setPos(mouseEvent->scenePos());
		tmpArrow->updatePosition();
		tmpArrow->update();
		//dw667 backmerge: was commented
		tmpConnector->updatePosition();
		
		tmpConnector->update();
		return;
    }
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}
//! [10]

//! [11]
void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (tmpArrow != 0) {
		NodeConnector* startC = tmpArrow->startConnector();
		NodeConnector* endC = tmpArrow->endConnector();
		QPointF startPos(startC->mapToScene(0, 0));
		QPointF endPos(endC->mapToScene(0, 0));
		//QPointF endPos(mouseEvent->scenePos());

		tmpArrow->startConnector()->setHighlight(false);
		tmpArrow->endConnector()->setHighlight(false);
		/*tmpArrow->startConnector()->updatePosition();
		tmpArrow->startConnector()->update();
		tmpArrow->endConnector()->updatePosition();
		tmpArrow->endConnector()->update();*/

		QList<QGraphicsItem *> startConnectors = items(startPos);
		while(startConnectors.count() && (startConnectors.first() == tmpArrow || startConnectors.first() == tmpConnector || startConnectors.first()->type() != NodeConnector::Type)) {
            startConnectors.removeFirst();
		}
		QList<QGraphicsItem *> endConnectors = items(endPos);
		while(endConnectors.count() && (endConnectors.first() == tmpArrow || endConnectors.first() == tmpConnector || endConnectors.first()->type() != NodeConnector::Type)) {
            endConnectors.removeFirst();
		}

		//removeItem(tmpArrow);

        delete tmpArrow;
		tmpArrow = 0;
		//dw now done in dtor, good idea?
		//dw new
		//removeItem(tmpConnector);
        delete tmpConnector;
		//tmpConnector->deleteLater();
		tmpConnector = 0;
        
		if (startConnectors.count() > 0 && endConnectors.count() > 0 &&
            startConnectors.first()->type() == NodeConnector::Type &&
			endConnectors.first()->type() == NodeConnector::Type &&
            startConnectors.first() != endConnectors.first())
		{
            NodeConnector *startConnector =
                qgraphicsitem_cast<NodeConnector *>(startConnectors.first());
            NodeConnector *endConnector =
                qgraphicsitem_cast<NodeConnector *>(endConnectors.first());

			//dw new: verify again:
			if (!((startConnector->connectorType() == NodeConnector::In && endConnector->connectorType() == NodeConnector::In) || (startConnector->connectorType() == NodeConnector::Out && endConnector->connectorType() == NodeConnector::Out)))
			{
				NodeConnection *arrow = new NodeConnection(startConnector, endConnector, NULL, this);
				arrow->setColor(mLineColor);
				startConnector->addConnection(arrow);
				endConnector->addConnection(arrow);
				arrow->setZValue(-1000.0);

				arrow->startConnector()->setHighlight(false);
				arrow->endConnector()->setHighlight(false);
				arrow->startConnector()->update();
				arrow->endConnector()->update();
			}

//            arrow->setZValue(2.0);
            //addItem(arrow);
			startConnector->setHighlight(false);
			endConnector->setHighlight(false);
            //arrow->updatePosition();
			//dw new

			/*startConnector->updatePosition();
			startConnector->update();
			endConnector->updatePosition();
			endConnector->update();*/
        }
			//NOTE: assumtion that lastHighlighted is never deleted while drawing lines, otherwise pointer can go to nirvana (TODO: can we use this assumtion?)
		if (lastHighlighted != NULL) {
			lastHighlighted->setHighlight(false);
			/*lastHighlighted->updatePosition();
			lastHighlighted->update();*/
			lastHighlighted = NULL;
		}
		return;
    }

//! [12] //! [13]
    //line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
//! [13]

//! [14]
bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}


void DiagramScene::setDebugDraw(bool enabled) {
	mDebugDraw = enabled;
	this->update();
}




