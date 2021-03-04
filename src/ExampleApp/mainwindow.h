#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "diagramscene.h"
#include "nodeitem.h"

class DiagramScene;

#include <QtCore>
#include <QtWidgets>
#include <QAction>
#include <QToolBox>
#include <QFrame>
#include <QSpinBox>
#include <QComboBox>
#include <QFontComboBox>
#include <QButtonGroup>
#include <QLineEdit>
#include <QGraphicsTextItem>
#include <QFont>
#include <QToolButton>
#include <QAbstractButton>
#include <QGraphicsView>
//class QGraphicsItem;


class ExampleDiagramScene;

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();

private slots:
    void backgroundButtonGroupClicked(QAbstractButton *button);
    void buttonGroupClicked(int id);
    void deleteItem();
    void pointerGroupClicked(int id);
    void bringToFront();
    void sendToBack();
    void sceneScaleChanged(const QString &scale);
    void lineColorChanged();
    void lineButtonTriggered();
    //void itemSelected(QGraphicsItem *item);
	void itemInserted(NodeItem* item);
    void about();

	void fileNew();
	void fileSave();
	void fileOpen();

public slots:
	void setNodeItemsStyle(const QString &styleName);
	void setNodeItemsStylesheet(const QString &stylesheetName);
	void setNoteItemsWindowFlags(Qt::WindowFlags flags);

private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();
    QWidget *createBackgroundCellWidget(const QString &text,
                                        const QString &image);
    //QWidget *createCellWidget(const QString &text,
    //                         DiagramItem::DiagramType type);
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);

    ExampleDiagramScene *scene;
    QGraphicsView *view;

    QAction *exitAction;
    QAction *addAction;
    QAction *deleteAction;

	//dw new5
	QAction *fileNewAction;
	QAction *fileSaveAction;
	QAction *fileOpenAction;

    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolbar;

	//dw new
	QCheckBox* debugDrawCheckbox;

    QComboBox *sceneScaleCombo;

    //QToolBox *toolBox;
	//QFrame *toolBox;
	QScrollArea *toolBox;

    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *lineColorToolButton;
    QAction *lineAction;

	QString currentStylesheet;
	Qt::WindowFlags currentWindowFlags;
};
//! [0]

class ExampleBaseNode : public NodeItem {
public:
	QGridLayout  *innerGridLayout;
	QHBoxLayout *topLayout;
	QVBoxLayout *leftLayout;
	QVBoxLayout *rightLayout;
	QHBoxLayout *bottomLayout;


    void setWidget(QWidget *widget) {
		//does this work for all possible wiget types
		NodeItem::setWidget(widget);
		widget->setObjectName("ExampleBaseNode");
	}
 

	ExampleBaseNode(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0, Qt::WindowFlags wFlags = 0) : NodeItem(contextMenu, parent, scene, wFlags) {
				//dw new
		QFrame *outterFrame = new QFrame;
		//QWidget *outterFrame = new QWidget;
		outterFrame->setObjectName("outterFrame");
		//QFormLayout *formlayout = new QFormLayout;

		QVBoxLayout* outterLayout = new QVBoxLayout;
		outterLayout->setMargin(0);


		//QGroupBox *innerFrame = new QGroupBox(outterFrame/*"Contact Details"*/);
		//QFrame *innerFrame = new QFrame(outterFrame/*"Contact Details"*/);
		//QFrame *innerFrame = new QFrame(outterFrame);
		//QWidget *innerFrame = new QWidget(outterFrame);
		QFrame *innerFrame = new QFrame();
		innerFrame->setObjectName("innerFrame");

		//QLineEdit *numberEdit = new QLineEdit;
		//QFormLayout *layout = new QFormLayout;
		//QGridLayout  *innerGridLayout = new QGridLayout;
		innerGridLayout = new QGridLayout;
		topLayout = new QHBoxLayout();
		//innerGridLayout->addLayout(topLayout, 0, 0, 1, 2/*, Qt::AlignCenter*/);
		QFrame *topFrame = new QFrame;
		topFrame->setLayout(topLayout);
		innerGridLayout->addWidget(topFrame, 0, 0, 1, 2/*, Qt::AlignCenter*/);
		leftLayout = new QVBoxLayout();
		//innerGridLayout->addLayout(leftLayout, 1, 0, 1, 1/*, Qt::AlignLeft*/);
		QFrame *leftFrame = new QFrame;
		leftFrame->setLayout(leftLayout);
		innerGridLayout->addWidget(leftFrame, 1, 0, 1, 1/*, Qt::AlignLeft*/);
		rightLayout = new QVBoxLayout();
		//innerGridLayout->addLayout(rightLayout, 1, 1, 1, 1/*, Qt::AlignRight*/);
		QFrame *rightFrame = new QFrame;
		rightFrame->setLayout(rightLayout);
		innerGridLayout->addWidget(rightFrame, 1, 1, 1, 1/*, Qt::AlignRight*/);
		bottomLayout = new QHBoxLayout();
		//innerGridLayout->addLayout(bottomLayout, 2, 0, 1, 2/*, Qt::AlignCenter*/);
		QFrame *bottomFrame = new QFrame;
		bottomFrame->setLayout(bottomLayout);
		innerGridLayout->addWidget(bottomFrame, 2, 0, 1, 2/*, Qt::AlignCenter*/);

		topLayout->setMargin(0);
		leftLayout->setMargin(0);
		rightLayout->setMargin(0);
		bottomLayout->setMargin(0);


		//dw newwww
		innerGridLayout->setMargin(0);
		/*
		innerGridLayout->addItem(new QSpacerItem(0,0),0,0);
		innerGridLayout->addItem(new QSpacerItem(0,0),0,1);
		innerGridLayout->addItem(new QSpacerItem(0,0),1,0);
		innerGridLayout->addItem(new QSpacerItem(0,0),1,1);
		*/


		/*
		addConnectorAndLabel("b1", NodeConnector::InOut, NodeConnector::Bottom);
		addConnectorAndLabel("righttest1", NodeConnector::InOut, NodeConnector::Right);
		addConnectorAndLabel("righttest2", NodeConnector::InOut, NodeConnector::Right);
		addConnectorAndLabel("b2", NodeConnector::InOut, NodeConnector::Bottom);
		addConnectorAndLabel("righttest3", NodeConnector::InOut, NodeConnector::Right);
		addConnectorAndLabel("lefttest1", NodeConnector::InOut, NodeConnector::Left);
		addConnectorAndLabel("lefttest2", NodeConnector::InOut, NodeConnector::Left);
		addConnectorAndLabel("lefttest3", NodeConnector::InOut, NodeConnector::Left);
		addConnectorAndLabel("b3", NodeConnector::InOut, NodeConnector::Bottom);
		addConnectorAndLabel("t1", NodeConnector::InOut, NodeConnector::Top);
		addConnectorAndLabel("t2", NodeConnector::InOut, NodeConnector::Top);
		addConnectorAndLabel("lefttest4", NodeConnector::InOut, NodeConnector::Left);
		addConnectorAndLabel("b4", NodeConnector::InOut, NodeConnector::Bottom);
		*/


		//formlayout->addWidget(innerFrame);
		//setWidget(innerFrame);
		//outterLayout->addWidget(innerFrame);

		//outterLayout->addLayout(innerGridLayout);
		innerFrame->setLayout(innerGridLayout);
		outterLayout->addWidget(innerFrame);

		//innerFrame->setLayout(innerGridLayout);
		outterFrame->setLayout(outterLayout);
		setWidget(outterFrame);


		outterFrame->setObjectName("ExampleBaseNode");
	}



	virtual void addConnectorAndLabel(QString name, NodeConnector::ConnectorType t, NodeConnector::ConnectorAlignment align) {
		int cols = innerGridLayout->columnCount();
		int rows = innerGridLayout->rowCount();

		QLabel* l = new QLabel(name);
		if (align == NodeConnector::Left) {
			l->setObjectName("leftLabel");
			l->setAlignment(Qt::AlignLeft);
			if (leftLayout->count() > 1) leftLayout->addStretch();
			leftLayout->addWidget(l);
			//leftLayout->addStretch();
		}
		else if (align == NodeConnector::Right) {
			l->setObjectName("rightLabel");
			l->setAlignment(Qt::AlignRight);
			if (leftLayout->count() > 1) rightLayout->addStretch();
			rightLayout->addWidget(l);
			//rightLayout->addStretch();
		}
		else if (align == NodeConnector::Top) {
			l->setObjectName("topLabel");
			l->setAlignment(Qt::AlignCenter);
			if (leftLayout->count() > 1) topLayout->addStretch();
			topLayout->addWidget(l);
			//topLayout->addStretch();
		} else if (align == NodeConnector::Bottom) {
			l->setObjectName("bottomLabel");
			l->setAlignment(Qt::AlignCenter);
			if (leftLayout->count() > 1) bottomLayout->addStretch();
			bottomLayout->addWidget(l);
			//bottomLayout->addStretch();
		}

		//innerGridLayout->upd

		addConnector(new NodeConnector(this, scene(), l, t, align, false));
	}


	virtual void serialize(QTextStream& out) {
		//QString res;
		//node
		out << "typeId=" << QString::number(getId()) << "\n";
		out << "uid=" << QString::number((size_t) this) << ", x=" << QString::number(pos().x()) << ", y=" << QString::number(pos().y()) << "\n";
		//connections that start on this node
		foreach(NodeConnector* con, connectors) {
			foreach(NodeConnection* c, con->arrows) {
				NodeConnector* oc = NULL;
				if (c->startConnector() == con) {
					oc = c->endConnector();
				}
				else {
					oc = c->startConnector();
				}
				ExampleBaseNode* oi = static_cast<ExampleBaseNode*>(oc->parentItem());
				//otherwise self-connections on this node (but not when on same connector) would be written twice, so do nothing in one of the two cases
				if (this == oi && this->connectors.indexOf(con) < oi->connectors.indexOf(oc)) {
					continue;
				}
				if (c->startConnector() == con) {
					out << "startNodeConnector=" << QString::number(this->connectors.indexOf(con));
					out << ", endNodeUid=" << QString::number((size_t) oi);
					out << ", endNodeConnector=" << QString::number(oi->connectors.indexOf(oc));
				}
				else {
					out << "endNodeConnector=" << QString::number(this->connectors.indexOf(con));
					out << ", startNodeUid=" << QString::number((size_t) oi);
					out << ", startNodeConnector=" << QString::number(oi->connectors.indexOf(oc));
				}
				out << "\n";
			}
		}
		out << "\n";
	}

	virtual void deserialize(QTextStream& out, QMap<int, ExampleBaseNode*>& map) {
		//typeId is read by caller
		QString  l;
		if ((l=out.readLine()) != "") {
			QStringList list = l.split(",");
			int id = list[0].split("=")[1].toInt();
			int x = list[1].split("=")[1].toInt();
			int y = list[2].split("=")[1].toInt();
			this->setPos(x, y);
			map[id] = this;
		}
		while ((l=out.readLine()) != "") {
			bool isStart = l.startsWith("startNodeConnector=");
			QStringList list = l.split(",");
			int c = list[0].split("=")[1].toInt();
			int oid = list[1].split("=")[1].toInt();
			int oc = list[2].split("=")[1].toInt();
			//only the second node creates the connection
			if (map.contains(oid)) {
				NodeItem* other = map[oid];
				NodeConnector* thisCon = this->connectors[c];
				NodeConnector* oCon = other->connectors[oc];
				NodeConnection* newCon = NULL;
				if (isStart) {
					newCon = new NodeConnection(thisCon, oCon, NULL, this->scene());
				}
				else {
					newCon = new NodeConnection(oCon, thisCon, NULL, this->scene());
				}
				//FIXME: should not be job of user
				thisCon->addConnection(newCon);
				oCon->addConnection(newCon);
				newCon->setZValue(-1000.0);
			}
		}
	}

	virtual int getId() = 0;
};

//"ExampleNode1: dialog, single in, only one connection"
class ExampleNode1 : public ExampleBaseNode {
public:
	ExampleNode1(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0) : ExampleBaseNode(contextMenu, parent, scene) {
		/*
		QLabel* in0 = new QLabel("in0");
		this->innerGridLayout->addWidget(in0);
		
		//dialog->setAttribute(Qt::WA_DeleteOnClose);
		//this->setWidget(dialog);

		addConnector(new NodeConnector(this, scene, in0, NodeConnector::In, NodeConnector::Left, true));
		*/
		//FIXME:
		addConnectorAndLabel("in0", NodeConnector::In, NodeConnector::Left);
	}
	int getId() { return 1; }
};

//"ExampleNode2: groupBox, single in, multi connection"
class ExampleNode2 : public ExampleBaseNode {
public:
	ExampleNode2(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0) : ExampleBaseNode(contextMenu, parent, scene) {
		/*
		QLabel* in0 = new QLabel("in0");

		innerGridLayout->addWidget(in0);
		
		//QGroupBox *dialog = new QGroupBox();
		//dialog->setLayout(layout);

		//dw668 was active: dialog->setAttribute(Qt::WA_DeleteOnClose);

		//this->setWidget(dialog);

		addConnector(new NodeConnector(this, scene, in0, NodeConnector::In, NodeConnector::Left, false));
		*/
		//FIXME:
		addConnectorAndLabel("in0", NodeConnector::In, NodeConnector::Left);
	}
	int getId() { return 2; }
};

//"ExampleNode5: dialog, single in, only one connection"
class ExampleNode5 : public ExampleBaseNode {
public:
	ExampleNode5(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0) : ExampleBaseNode(contextMenu, parent, scene) {
		//QFormLayout *layout2 = new QFormLayout;
		/*
		QLabel* out0 = new QLabel("out0");
		out0->setAlignment(Qt::AlignRight);
		QLabel* in0 = new QLabel("in0");
		
		innerGridLayout->addWidget(in0,0,0);
		innerGridLayout->addWidget(out0,0,1);
		QLabel* in1 = new QLabel("in1");
		innerGridLayout->addWidget(in1,1,0,1,2);
		QLabel* in2 = new QLabel("in2");
		innerGridLayout->addWidget(in2,2,0,1,2);
		QLabel* inout0 = new QLabel("inOut0");
		inout0->setAlignment(Qt::AlignRight);
		innerGridLayout->addWidget(inout0,3,0,1,2);

		QSpinBox* spinBox = new QSpinBox();
		spinBox->setMinimum(0);
		spinBox->setMaximum(9);
		innerGridLayout->addWidget(spinBox,4,0,1,2);
		*/

		addConnectorAndLabel("in0", NodeConnector::In, NodeConnector::Left);
		addConnectorAndLabel("out0", NodeConnector::Out, NodeConnector::Right);
		addConnectorAndLabel("in1", NodeConnector::In, NodeConnector::Left);
		addConnectorAndLabel("in2", NodeConnector::In, NodeConnector::Left);
		addConnectorAndLabel("inOut0", NodeConnector::InOut, NodeConnector::Right);
		QSpinBox* spinBox = new QSpinBox();
		spinBox->setMinimum(0);
		spinBox->setMaximum(9);
		leftLayout->addWidget(spinBox);
		addConnector(new NodeConnector(this, scene, spinBox, NodeConnector::InOut));


		//QDialog *dialog1 = new QDialog();
		//dw from: http://lists.trolltech.com/qt-interest/2002-05/thread00837-0.html
		//MyDialog::MyDialog(QWidget* parent, const char* name)	: QDialog(parent, name, true, WStyle_Customize | WStyle_DialogBorder | WStyle_Title | WStyle_SysMenu)

		/*
		QDialog *dialog1 = new QDialog(NULL, Qt::WindowType::FramelessWindowHint);
		dialog1->setLayout(layout2);
		*/

		//dialog1->setAttribute(Qt::WA_DeleteOnClose);

		//dw new3
		//dialog1->setStyle(new QStyle::());

		//dialog1->setSizeGripEnabled(false);

		//dialog1->setFixedSize(dialog1->size());
		//dialog1->setSizePolicy(QSizePolicy::Fixed);
		//layout2->setSizeConstraint(QLayout::SetFixedSize);

		//dialog1->layout()->setSizeConstraint( QLayout::SetFixedSize ) ;
		//dialog1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		

		/*
		this->setWidget(dialog1);
		setWindowFlags(dialog1->windowFlags() | Qt::Tool);
		*/
		/*
		addConnector(new NodeConnector(this, scene, out0, NodeConnector::Out, NodeConnector::Right));
		addConnector(new NodeConnector(this, scene, in0, NodeConnector::In));
		addConnector(new NodeConnector(this, scene, in1, NodeConnector::In));
		addConnector(new NodeConnector(this, scene, in2, NodeConnector::In));
		addConnector(new NodeConnector(this, scene, inout0, NodeConnector::InOut, NodeConnector::Right));
		addConnector(new NodeConnector(this, scene, spinBox, NodeConnector::InOut));
		*/
	}
	int getId() { return 5; }
};

//"ExampleNode6: groupBox, 2x inout, multi connection"
class ExampleNode6 : public ExampleBaseNode {
public:
	ExampleNode6(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0) : ExampleBaseNode(contextMenu, parent, scene) {

		addConnectorAndLabel("inout0", NodeConnector::InOut, NodeConnector::Left);
		addConnectorAndLabel("inout1", NodeConnector::InOut, NodeConnector::Right);

		/*
		//QFormLayout *layout = new QFormLayout;
		QLabel* inout0 = new QLabel("inout0");
		QLabel* inout1 = new QLabel("inout1");
		inout1->setAlignment(Qt::AlignRight);
		//layout->addRow(inout0, inout1);
		//QGroupBox *dialog = new QGroupBox();
		//dialog->setLayout(layout);

		innerGridLayout->addWidget(inout0,0,0);
		innerGridLayout->addWidget(inout1,0,1);
		*/

		/*
		dialog->setAttribute(Qt::WA_DeleteOnClose);
		this->setWidget(dialog);
		//dw with Qt:Tool they seem to be movable by click!!! but bar has same size on windows vista
		setWindowFlags(dialog->windowFlags() | Qt::Tool | Qt::WindowType::FramelessWindowHint);
		*/

		/*
		addConnector(new NodeConnector(this, scene, inout0, NodeConnector::InOut, NodeConnector::Left, false));
		addConnector(new NodeConnector(this, scene, inout1, NodeConnector::InOut, NodeConnector::Right, false));
		*/
	}
	int getId() { return 6; }
};

//"ExampleNode7: frame with title, 1 x out, multi connection"
class ExampleNode7 : public ExampleBaseNode {
public:
	ExampleNode7(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0) : ExampleBaseNode(contextMenu, parent, scene, Qt::WindowType::Dialog | Qt::CustomizeWindowHint | Qt::WindowType::MSWindowsFixedSizeDialogHint | Qt::WindowType::WindowTitleHint | Qt::Tool) {
		addConnectorAndLabel("out0", NodeConnector::Out, NodeConnector::Right);

		/*
		//QFormLayout *layout = new QFormLayout;
		QLabel* out0 = new QLabel("out0");
		out0->setAlignment(Qt::AlignRight);
		*/
		/*
		layout->addRow(out0);
		QDialog *dialog = new QDialog(NULL);
		dialog->setWindowTitle("ExampleNode7: frame with title, 1 x out, multi connection");
		//QToolBox *dialog = new QToolBox();
		dialog->setWindowTitle("xxx7");
		dialog->setLayout(layout);
		//dialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		//dialog->setFixedSize(dialog->sizeHint());
		//layout->setSizeConstraint(QLayout::SetFixedSize);
		this->mNoResize = false;
		*/

		//dialog->setAttribute(Qt::WA_DeleteOnClose);
		//this->setWidget(dialog);

		/*
		innerGridLayout->addWidget(out0);
		addConnector(new NodeConnector(this, scene, out0, NodeConnector::Out, NodeConnector::Right, false));
		*/
	}
	int getId() { return 7; }
};

//"ExampleNode8: only groupBox"
class ExampleNode8 : public ExampleBaseNode {
public:
	ExampleNode8(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0) : ExampleBaseNode(contextMenu, parent, scene) {

		addConnectorAndLabel("t0", NodeConnector::InOut, NodeConnector::Top);
		addConnectorAndLabel("t1", NodeConnector::InOut, NodeConnector::Top);
		addConnectorAndLabel("t2", NodeConnector::InOut, NodeConnector::Top);

		addConnectorAndLabel("l0", NodeConnector::InOut, NodeConnector::Left);
		addConnectorAndLabel("l1", NodeConnector::InOut, NodeConnector::Left);
		addConnectorAndLabel("l2", NodeConnector::InOut, NodeConnector::Left);

		addConnectorAndLabel("r0", NodeConnector::InOut, NodeConnector::Right);
		addConnectorAndLabel("r1", NodeConnector::InOut, NodeConnector::Right);
		addConnectorAndLabel("r2", NodeConnector::InOut, NodeConnector::Right);

		addConnectorAndLabel("b0", NodeConnector::InOut, NodeConnector::Bottom);
		addConnectorAndLabel("b1", NodeConnector::InOut, NodeConnector::Bottom);
		addConnectorAndLabel("b2", NodeConnector::InOut, NodeConnector::Bottom);



	}
	int getId() { return 8; }
};

class ExampleDiagramScene : public DiagramScene {
public:
	int mode;
	ExampleDiagramScene(QMenu *itemMenu, QObject* parent = 0) : DiagramScene(itemMenu, parent ), mode(0) {
	}
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
		if (mode == 0) {
			DiagramScene::mousePressEvent(mouseEvent);
		}
		else {
			NodeItem *node2 = createNode(mode);
			//this->addItem(node2);
			node2->setPos(mouseEvent->scenePos());
			mode = 0;
		}
	}
	ExampleBaseNode* createNode(int type) {
		ExampleBaseNode *node2 = NULL;
		switch (type) {
			case 1:
				node2 = new ExampleNode1(mItemMenu,NULL,this);
				break;
			case 2:
				node2 = new ExampleNode2(mItemMenu,NULL,this);
				break;
			case 5:
				node2 = new ExampleNode5(mItemMenu,NULL,this);
				break;
			case 6:
				node2 = new ExampleNode6(mItemMenu,NULL,this);
				break;
			case 7:
				node2 = new ExampleNode7(mItemMenu,NULL,this);
				break;
			case 8:
				node2 = new ExampleNode8(mItemMenu,NULL,this);
				break;
		}
		emit nodeItemInserted(node2);
		return node2;
	}
};




class MyFasterGraphicView : public QGraphicsView
{
Q_OBJECT
public:
	MyFasterGraphicView(QGraphicsScene* scene): QGraphicsView(scene) {}
protected:
	void paintEvent ( QPaintEvent * event) {
		QPaintEvent *newEvent=new QPaintEvent(event->region().boundingRect());
		QGraphicsView::paintEvent(newEvent);
		delete newEvent;
	}
};


#endif
