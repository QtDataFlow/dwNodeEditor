//dw 
//#include <QtGui>

#include "nodeitem.h"

//#include "arrow.h"
//dw
//#include "nodeconnector.h"

void NodeItem::hide() {
	this->widget()->close();
}

//dw slot
void NodeItem::deleted() {
	this->widget()->close();
	//delete this;
}

void NodeItem::deleted(int result) {
	this->widget()->close();
}

NodeItem::~NodeItem() {
	removeWigetFromConnectors();
	//deleteConnections();
	//dw new 
	if (scene() != NULL) {
		this->scene()->removeItem(this);
	}
}

//! [0]
NodeItem::NodeItem(QMenu *contextMenu,
					 QGraphicsItem *parent, /*//dw can we really assume our scene type*/ QGraphicsScene /*DiagramScene*/ *scene, Qt::WindowFlags wFlags)
			 : /*QGraphicsPolygonItem(parent, scene) //dw*/ /*QFrame(parent->parentWidget(), 0)*/
QGraphicsProxyWidget(parent, /*//dw668: did this cause decorations now in 4.7 but no in 4.5.2?: Qt::Window*/ wFlags), mMaxRadius(1)
{
	//dw new4: is this a problem? check it
    setCacheMode(DeviceCoordinateCache);

    mContextMenu = contextMenu;
	isMoving = false;

	//dw new:
	setZValue(1);
	//param
	mNoResize = true;
	if (mNoResize) {
		mControlResizeHandles = true;
	}
	else {
		//param
		mControlResizeHandles = false;
	}


/*
    QPainterPath path;

	 //dw
	 //QGroupBox *groupBox = new QGroupBox("GrBox");
	 //QLabel *numberLabel = new QLabel("Telephone number");
	 //QLineEdit *numberEdit = new QLineEdit;
	 //QFormLayout *layout = new QFormLayout;
	 //layout->addRow(numberLabel, numberEdit);
	 //groupBox->setLayout(layout);
	 QFormLayout *layout2 = new QFormLayout;
	 //layout2->addRow(groupBox);

	 QLabel* out0 = new QLabel("out0");
	 out0->setAlignment(Qt::AlignRight);
	 QLabel* in0 = new QLabel("in0");
	 layout2->addRow(in0, out0);
	 QLabel* in1 = new QLabel("in1");
	 layout2->addRow(in1);
	 QLabel* in2 = new QLabel("in2");
	 layout2->addRow(in2);
	 QLabel* inout0 = new QLabel("inOut0");
	 inout0->setAlignment(Qt::AlignRight);
	 layout2->addRow(inout0);

	 //QSpinBox ( int minValue, int maxValue, int step = 1, QWidget * parent = 0, const char * name = 0 )
	 QSpinBox* spinBox = new QSpinBox();
	 spinBox->setMinimum(0);
	 spinBox->setMaximum(9);
	 layout2->addRow(spinBox);

	 QDialog *dialog1 = new QDialog();
	 //QFrame *dialog1 = new QFrame();
	 //QGroupBox* dialog1 = new QGroupBox("A QGroupBox");
	 dialog1->setLayout(layout2);
	 //dialog1->setLayout(groupBox);
	 //this->setWidget(groupBox);
	 //dw will this fix deletion not called on close?
	 dialog1->setAttribute(Qt::WA_DeleteOnClose);
	 this->setWidget(dialog1);

	 addConnector(new NodeConnector(this, scene, out0, NodeConnector::Out, true));
	 addConnector(new NodeConnector(this, scene, in0, NodeConnector::In));
	 addConnector(new NodeConnector(this, scene, in1, NodeConnector::In));
	 addConnector(new NodeConnector(this, scene, in2, NodeConnector::In));
	 addConnector(new NodeConnector(this, scene, inout0, NodeConnector::InOut, true));

	 addConnector(new NodeConnector(this, scene, spinBox, NodeConnector::InOut));
	 
	 //QGraphicsScene scene;
	 //QGraphicsProxyWidget *proxy = scene->addWidget(groupBox);
	 //QGraphicsView view(&scene);
	 //view.show();
*/

/*    setPolygon(mPolygon);*/
	 setFlag(QGraphicsItem::ItemIsMovable, true);
	 setFlag(QGraphicsItem::ItemIsSelectable, true);
	 setFlag(QGraphicsItem::ItemIsFocusable, true);


	 //dw why is that needed
	 //dialog1->setWindowFlags(Qt::WindowMov);
	 //widget()->setWindowFlags(Qt::WindowFlags);

	 //dw new
	 if (scene != NULL){
		scene->addItem(this);
	 }
	 

/*
QDialog signals:
void 	accepted ()
void 	finished ( int result )
void 	rejected ()
*/
	 /*
	 connect(dialog1, SIGNAL(accepted()), this, SLOT(deleted()));
	 connect(dialog1, SIGNAL(finished(int)), this, SLOT(deleted(int)));
	 connect(dialog1, SIGNAL(rejected()), this, SLOT(deleted()));
	 */

/*
QWidget signals:
void 	customContextMenuRequested ( const QPoint & pos )
*/
/*
QObject signals:
void 	destroyed ( QObject * obj = 0 )
*/

	//dw big problem: we do not have dialog1 here with new design, but when to do it? ==> override setWidget()
	//connect(dialog1, SIGNAL(destroyed()), this, SLOT(deleted()));
}
//! [0]


QRectF NodeItem::boundingRect() const
{
	/*
    qreal adjust = 5;
    return QRectF(-radius - adjust, -radius - adjust,
                  2*(radius + adjust), 2*(radius + adjust));
				  */

	//dw new
	QRectF rec(QGraphicsProxyWidget::boundingRect());
	//order matters!!!
	//rec.setX(rec.x() - 2 * (mMaxRadius));
	//rec.setWidth(rec.width() + 2 * (mMaxRadius));
	qreal extra = 3;//2 * (mMaxRadius) ;
	rec = rec.normalized().adjusted(-extra, 0, extra, 0);

	//rec.setWidth(rec.width() - 2 * (mMaxRadius + 1));
	//rec.setX(rec.x() + (mMaxRadius + 1));
	//rec.setWidth(rec.width() - 4);
	//rec.setX(rec.x() + 2);
	return rec;
}

QPainterPath NodeItem::shape() const {

	QPainterPath p;// = QGraphicsProxyWidget::shape();
	QRectF rec(QGraphicsProxyWidget::boundingRect());
	//rec.setWidth(rec.width() - 2 * (mMaxRadius + 1));
	//rec.setX(rec.x() + (mMaxRadius + 1));
	p.addRect(rec);
	
	/*//exclude children
	foreach (NodeConnector *c, connectors) {
		//dw problem: label already deleted but connector tries to enable it?
        //c->deleteConnections();
		p = p.subtracted(c->shape());
    }*/

	/*//add children
	foreach (NodeConnector *c, connectors) {
		p.addPath(this->mapFromItem(c, c->shape()));
    }*/

	return p;
}


void NodeItem::setWidget(QWidget *widget) {
	//does this work for all possible wiget types
	QGraphicsProxyWidget::setWidget(widget);
	connect(widget, SIGNAL(destroyed()), this, SLOT(deleted()));
}

void NodeItem::addConnector(NodeConnector* nc) {
	connectors.append(nc);
	if (nc->mRadius > mMaxRadius) {
		mMaxRadius = nc->mRadius;
	}

	updateConnectorsPos();
	prepareGeometryChange();
}


//! [2]
void NodeItem::deleteConnections()
{
    foreach (NodeConnector *c, connectors) {
		//dw problem: label already deleted but connector tries to enable it?
        c->deleteConnections();
    }

	//dw good location?, needed?
	//this->scene()->removeItem(this);
}
//! [2]

void NodeItem::removeWigetFromConnectors() {
	foreach (NodeConnector *c, connectors) {
		//dw problem: label already deleted but connector tries to enable it?
        c->removeWidget();
    }
}

//! [5]
void NodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
	//dw new3
    //mContextMenu->exec(event->screenPos());
	if (mContextMenu != NULL) {
		mContextMenu->exec(event->screenPos());
	}
}
//! [5]

//! [6]
QVariant NodeItem::itemChange(GraphicsItemChange change, //dw FIXME: needs much cleanup
                     const QVariant &value)
{

	//dw now in paint, check if this is a good idea (e.g. when is it called)
	//dw667 backmerge: was commented, but is shotgun approach!!!
	if (change == QGraphicsItem::ItemPositionChange) {
		updateConnectorsPos();
	}
   //does this create loop on selection?
   

   //dw if visibilty changes to false, kill wiget (TODO: make configurable, usfull for Dialogs and such)
   if (change == QGraphicsItem::ItemVisibleHasChanged && !value.value<bool>()) {
	   deleted();
	   return value;
   }



   /*
   //dw 669: turn back on resize handle controlling
   //dw new3: do not allow cursor changes, better only over connector!
   */
   if (mControlResizeHandles && change == QGraphicsItem::ItemCursorChange) {
       QCursor cur = value.value<QCursor>();
	   //FIXME: do we really have to do this by hand?
	   //suppress all resizes
	   if (cur.shape() == Qt::SizeVerCursor || cur.shape() == Qt::SizeHorCursor || cur.shape() == Qt::SizeBDiagCursor || cur.shape() == Qt::SizeFDiagCursor) {
		   if (mNoResize) {
               return QVariant::fromValue(Qt::ArrowCursor);
		   }
           else {       //QCursor cur = qVariantValue<QCursor>(value);
	   			foreach (NodeConnector *con, connectors) {
					if (con->isUnderMouse()) {
                        return QVariant::fromValue(Qt::ArrowCursor);
					}
				}
		   }
	   }
   }/**/

   
   //dw 669: turn back on resize handle controlling
   //dw ugly hack, find better way
   //dw deselecting proxy item dialog will cause error sometimes, has size of bounding rect, will not redraw connections 
   if (change == QGraphicsItem::ItemSelectedChange || change == QGraphicsItem::ItemTransformChange || change == QGraphicsItem::ItemScaleChange
	   || change == QGraphicsItem::ItemSendsGeometryChanges || change == QGraphicsItem::ItemMatrixChange) {
	   /*
		foreach (NodeConnector *con, connectors) {
			con->updatePositionGeometry();
		}
		*/
	   updateConnectorsPos();
   }
   if (change == QGraphicsItem::ItemPositionHasChanged || change == QGraphicsItem::ItemSelectedChange) {
	   /*
		foreach (NodeConnector *con, connectors) {
			con->updatePositionGeometry();
		}
		*/
	   updateConnectorsPos();
   }

   
   /*//dw debug help
   if (change == QGraphicsItem::ItemSelectedChange || change == QGraphicsItem::ItemEnabledChange || change == QGraphicsItem::ItemVisibleHasChanged || change == QGraphicsItem::ItemPositionChange
	   || change == QGraphicsItem::ItemZValueChange || change == QGraphicsItem::ItemZValueHasChanged) {
	    //scene()->clearSelection();
		//setSelected(true);
		//return true;
		return QGraphicsProxyWidget::itemChange(change, value);
	}*/


	return QGraphicsProxyWidget::itemChange(change, value);
    //return value;
}
//! [6]

//dw669: new, fixes connector position on resizing, why can it not be done in itemChange?
	void NodeItem::resizeEvent ( QGraphicsSceneResizeEvent * event ) {
		QGraphicsProxyWidget::resizeEvent(event);
		updateConnectorsPos();
	}

//dw new4: remove again
void NodeItem::hoverMoveEvent ( QGraphicsSceneHoverEvent * event )  {
	event->ignore();
	return;
}

void NodeItem::updateConnectorsPos() {
	foreach (NodeConnector *con, connectors) {
		//dw667 backmerge: was active
        //con->updatePositionGeometry();
		//dw new
		con->updatePosition();
    }
	//dw667: was active
	//update();
}


void NodeItem::debugPaint(QPainter *painter) {
	//dw debug
	static int i = 0, j=0, k=0;
	painter->fillRect(boundingRect(), /*Qt::green*/ QColor(i=(i+19)%256 , j=(j+51)%256, k=(k+11)%256)); // to see item.
	//painter->fillPath(shape(), QColor(i=(i+19)%256 , j=(j+51)%256, k=(k+11)%256));
}


//dw
void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
	if (static_cast<DiagramScene*>(scene())->isDebugDraw()) {
		debugPaint(painter);
	}
	//dw new
	//dw667: was active
	//updateConnectorsPos();

	QGraphicsProxyWidget::paint(painter, option, w);
	//dw new2
	//QGraphicsItem::paint(painter, option, w);

	//dw new3: why do we have to call paint of children???
	//dw667: was active
	/*
	foreach (NodeConnector *c, connectors) {
		//dw problem: label already deleted but connector tries to enable it?
        c->paint(painter, option, w);
		c->update();
    }
	*/
}

/*
//dw new3
void NodeItem::update(const QRectF & rect) {
	
	//dw new3: why do ourself
	foreach (NodeConnector *c, connectors) {
		//dw problem: label already deleted but connector tries to enable it?
        //c->paint(painter, option, w);
		c->update(rect);
    }
	
	QGraphicsProxyWidget::update(rect);
}
*/


//dw TODO: move to good visible location, check which types should be included
//const char* NodeItem::shouldNotMoveTypes[] = {"QLineEdit", "foo", "bar"};
const char* NodeItem::shouldMoveOnClickTypes[] = {"QDialog", "QFrame", "QGroupBox"};


bool NodeItem::shouldMoveNode(QGraphicsSceneMouseEvent *mouseEvent) {
	QPointF pos = mouseEvent->pos();
	QPointer<QWidget> hitWidget = widget()->childAt(pos.toPoint());
	if (hitWidget == NULL) {
		return true;
	}
	//foreach(QString t, shouldNotMoveTypes) {
	//	if (alienWidget->inherits(t.toStdString().c_str())) {
	const size_t len = sizeof(shouldMoveOnClickTypes) / sizeof(shouldMoveOnClickTypes[0]);
	for (size_t i = 0; i < len; ++i) {
		if (hitWidget->inherits(shouldMoveOnClickTypes[i])) {
			return true;
		}
	}
	return false;
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	if (shouldMoveNode(mouseEvent)) {
		QGraphicsItem::mousePressEvent(mouseEvent);
		isMoving = true;
		// what if we have to remove that?
		scene()->clearSelection();
		scene()->clearFocus();
		setSelected(true);
	}
	else {
		QGraphicsProxyWidget::mousePressEvent(mouseEvent);
	}
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	if (isMoving) {
		QGraphicsItem::mouseMoveEvent(mouseEvent);

		//dw667 backmerge: was active
		/*
		//dw new5
		foreach (NodeConnector *con, connectors) {
			//dw667 backmerge: was active
			//con->updatePositionGeometry();
			//dw667 backmerge: new
			con->updatePosition();
		}
		*/
	}
	else {
		QGraphicsProxyWidget::mouseMoveEvent(mouseEvent);
	}

	//scene()->clearSelection();
	//setSelected(true);

	//dw667 backmerge: was active
	//updateConnectorsPos();
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	if (isMoving) {
		isMoving = false;
	}
	//call both always to lose no events and to not have to do the same shit for clicks too
	QGraphicsItem::mouseReleaseEvent(mouseEvent);
	QGraphicsProxyWidget::mouseReleaseEvent(mouseEvent);
	scene()->clearSelection();
	setSelected(true);

	//updateConnectorsPos();
}


