#include "object.h"
#include <qmath.h>

void Human::drawAt(double time)
{
    glTranslated(initX_,initY_,0.0);
	p_.walk(speed_*time);
	OpenGLTools::drawHuman();
}

void Object::addPathItem(double x, double y)
{
    double angle = atan(y/x) * 180 / M_PI;
    double d = x / cos(angle * M_PI / 180);
    d = d < 0 ? -d : d;
    angle = x < 0 ? 180+angle : angle;
    angle -= currentAngle;
    currentAngle += angle;
    p_.wps_.push_back(WayPoint(d, angle));
    p_.totalLength_ += d;
}

void SmallCar::drawAt(double time)
{
    glTranslated(initX_,initY_,0.0);
	p_.walk(speed_*time);
	OpenGLTools::drawSmallCar();
}

void LargeCar::drawAt(double time)
{
    glTranslated(initX_,initY_,0.0);
	p_.walk(speed_*time);
	OpenGLTools::drawLargeCar();
}
