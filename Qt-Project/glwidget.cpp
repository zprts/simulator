#include "glwidget.h"
#include <iostream>


GLWidget::GLWidget(QWidget *parent) :
QGLWidget(parent), cc_(CamerasContainer::getInstance())
{
	setMouseTracking(false);
}

void GLWidget::initializeGL() {
	glClearColor(0, 0, 0.6f, 1);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
//	glEnable(GL_LIGHTING);
//	GLfloat ambient_light[ 4 ] =
//	{
//		1.0, 1.0, 1.0, 0.1
//	};
//	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_light );
	try {
		Tile::initTextures();
	} catch (Exception &e) {
		QMessageBox::information(nullptr, "Loading texture error", e.getDesc());
		QCoreApplication::exit(1);	//Hmmm, probably exist a little bit more elegant solution...
	}
    Simulation::getInstance()->load("");
    //Simulation::getInstance()->readJSon();
}
void GLWidget::paintGL() {
	cc_.use();
	if (!cc_.currentCamValid()) {
		cc_.free();
		return;
	}
	Camera *c = cc_.getCurrentCam();
	c->genView(Simulation::getInstance());
	cc_.free();
}
void GLWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w/h, 0.01f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void GLWidget::test() {
	//QMessageBox::information(nullptr, "", QString::number(a.a));
	/*
	timer_.stop();
	glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		Tile t;
		t.draw();
		float tab[4]{};
		glGetFloatv(GL_VIEWPORT, tab);
		//QMessageBox::information(nullptr, "Size...", QString("[ %1 x %2 ] --- [ %3 x %4 ]").arg(tab[0]).arg(tab[1]).arg(tab[2]).arg(tab[3]));
		QImage img(tab[2], tab[3], QImage::Format_RGB32);
		glReadPixels(0, 0, tab[2], tab[3], GL_BGRA, GL_UNSIGNED_BYTE, img.bits());
		//img = img.rgbSwapped();
		//QMessageBox::information(nullptr, "a", "a");
		if (glGetError()) {
			//QMessageBox::information(nullptr, "", "");
		}
		QString str = "test.bmp"; //QCoreApplication::applicationDirPath() + "/test.bmp";
		bool r = img.save(str);
		//QMessageBox::information(nullptr, "b", QString("b %1").arg(static_cast<int>(r)));
	glPopMatrix();
	timer_.start();
	*/
	//glLoadIdentity();
	//gluLookAt(0.0, 2.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

	QPoint p = event->pos() - point_;
	point_ = event->pos();
	cc_.use();
	if (!cc_.currentCamValid()) {
		cc_.free();
		return;
	}

	if (event->buttons() & Qt::RightButton) {
		cc_.cameras_[cc_.currentCam].rotate(p);
	} else if (event->buttons() & Qt::LeftButton) {
		cc_.cameras_[cc_.currentCam].moveXY(p);
	} else if (event->buttons() & Qt::MiddleButton) {
		cc_.cameras_[cc_.currentCam].distance(p);
	}
	cc_.free();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    point_ = event->pos();
    std::cout << point_.x() << "xx" << point_.y();
    if (addPointMode) {
        QVector3D pos = getPos(point_.x(), point_.y());

        d_->addPoint(pos.x(), pos.y());
        addPointMode = false;
        //d_->setModal(true);

        //QList<QStandardItem *> list;
        //list << new QStandardItem("mru");

        //pointModel->appendRow(list);
        //pointModel->appendRow(new QStandardItem("QString::number(3.0d)"));

    //if (mouse == 0) {
        //std::cout<<pos.x()<<std::endl;
        //Simulation::getInstance()->add(pos.x(),pos.y(),pos.z());
        //mouse++;
    //} else if (mouse == 1) {
        //Simulation::getInstance()->addWayPoint(pos.x(),pos.y());
    //}
    }
}

QVector3D GLWidget::getPos(int posX, int posY)
{
    GLdouble x1, y1, z1;
    GLdouble x2, y2, z2;
    GLdouble winX, winY;

    GLdouble model_view[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
    GLdouble projection[16];
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = posX;
    double scale = (double)viewport[2]/256;
    winY = viewport[3]-posY;

    gluUnProject(winX, winY, 0.0d, model_view, projection,
    viewport, &x1, &y1, &z1);

    gluUnProject(winX, winY, 1.0d, model_view, projection,
    viewport, &x2, &y2, &z2);

    QVector3D point = {(float)x1, (float)y1, (float)z1};
    QVector3D v = {(float)(x2-x1), (float)(y2-y1), (float)(z2-z1)};

    float d = (0 - z1)/v.z();

    point = point + d*v;
    return point;
}

void GLWidget::setDialog(Dialog *d)
{
    d_ = d;
}

void GLWidget::setAddPointMode(bool mode) {
    addPointMode = mode;
}
