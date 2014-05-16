#include "object.h"

void Human::drawAt(double time)
{
	Tile::initPos(initTileX_, initTileY_, initTilePos_, tileDParam_);
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
	p_.wps_.push_back(WayPoint(1.0d, 90.0d * static_cast<double>(dir)));
	p_.totalLength_ += 1.0d;
}



void SmallCar::drawAt(double time)
{
	Tile::initPos(initTileX_, initTileY_, initTilePos_, tileDParam_);
	glRotated(static_cast<double>(oid_) * 90.0d, 0.0, 0.0, 1.0);
	p_.walk(speed_*time);
	OpenGLTools::drawSmallCar();
}

void LargeCar::drawAt(double time)
{
	Tile::initPos(initTileX_, initTileY_, initTilePos_, tileDParam_);
	glRotated(static_cast<double>(oid_) * 90.0d, 0.0, 0.0, 1.0);
	p_.walk(speed_*time);
	OpenGLTools::drawLargeCar();
}
