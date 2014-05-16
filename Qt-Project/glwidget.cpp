#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent) :
QGLWidget(parent), cc_(CamerasContainer::getInstance())
{
	setMouseTracking(false);
}

void GLWidget::initializeGL() {
	glClearColor(0, 0, 0.6f, 1);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
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
}
