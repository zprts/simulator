#include "object.h"
#include <qmath.h>

void Human::drawAt(double time)
{
    //Tile::initPos(initTileX_, initTileY_, initTilePos_, tileDParam_);
    glTranslated(initTileX_,initTileY_,0.0);
	glRotated(static_cast<double>(oid_) * 90.0d, 0.0, 0.0, 1.0);
	p_.walk(speed_*time);
	OpenGLTools::drawHuman();
}

void Object::addPathItem(PIDir dir, PIR pir)
{
	if (dir == PIDir::Forward || dir == PIDir::Backward) {
		addStraightPathItem(dir);
	} else {
		p_.addTurnPathItem(dir, pir, tileDParam_);
	}
}


void Object::addStraightPathItem(PIDir dir)
{
    p_.wps_.push_back(WayPoint(0.5d, 90.0d * static_cast<double>(dir)));
    p_.totalLength_ += 0.5d;
}

void Object::addPathIt(double x, double y)
{
    //double x1 = x - initTileX_;
    //double y1 = y - initTileY_;

    double angle = atan(y/x) * 180 / M_PI;
    double d = x / cos(angle * M_PI / 180);
    d = d < 0 ? -d : d;
    //currentAngle += angle;
    angle = x < 0 ? 180+angle : angle;
    angle -= currentAngle;
    currentAngle += angle;
    p_.wps_.push_back(WayPoint(d, angle));
    p_.totalLength_ += d;
}

void SmallCar::drawAt(double time)
{
    //Tile::initPos(initTileX_, initTileY_, initTilePos_, tileDParam_);
    glTranslated(initTileX_,initTileY_,0.0);
	glRotated(static_cast<double>(oid_) * 90.0d, 0.0, 0.0, 1.0);
	p_.walk(speed_*time);
	OpenGLTools::drawSmallCar();
}

void LargeCar::drawAt(double time)
{
    //Tile::initPos(initTileX_, initTileY_, initTilePos_, tileDParam_);
    glTranslated(initTileX_,initTileY_,0.0);
	glRotated(static_cast<double>(oid_) * 90.0d, 0.0, 0.0, 1.0);
	p_.walk(speed_*time);
	OpenGLTools::drawLargeCar();
}
