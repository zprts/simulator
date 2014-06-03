#ifndef TOOLS_H
#define TOOLS_H

#include <QGLWidget>
#include <QImage>
#include <QException>
#include <GL/glu.h>
#include <memory>

class Exception : public QException {
public:
	Exception(QString desc) {
		desc_ = desc;
	}
	QString getDesc() {
		return desc_;
	}
private:
	QString desc_;
};

class OpenGLTools
{
public:
	//OpenGLTools();
	static GLuint	loadTexture(QString path) throw (Exception);
	static void		drawPlane();
	static void		drawCube();
	static void		drawHuman();
	static void		drawSmallCar();
	static void		drawLargeCar();
private:
    static std::auto_ptr<GLUquadric> quadric_;
};



#endif // TOOLS_H
