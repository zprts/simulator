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
    Simulation::getInstance()->load();
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

/*!
 * \brief GLWidget::mousePressEvent
 * Pobiera pozycję kursora na ekranie. Jeśli dodatkowo jest włączony tryb PointMode, dodaje
 * do okna dialogowa współrzędne wskazanego punktu.
 * \param event
 */
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    point_ = event->pos();
    if (addPointMode) {
        QVector3D pos = getPos(point_.x(), point_.y());
        d_->addPoint(pos.x(), pos.y());
        addPointMode = false;
    }
}

/*!
 * \brief GLWidget::getPos
 * Na podstawie dwuwymiarowego punktu na ekranie, oblicza odpowiadający mu trójwymiarowy punkt
 * w scenie 3D
 * \param posX współrzędna x punktu na ekranie
 * \param posY współrzędna y punktu na ekranie
 * \return punkt w scenie 3D
 */
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
/*!
 * \brief GLWidget::setAddPointMode
 * Przełącza tryb w którym użytkownik może wskazać punkt, który zostanie dodany do scenariusza.
 * \param mode
 */
void GLWidget::setAddPointMode(bool mode) {
    addPointMode = mode;
}
