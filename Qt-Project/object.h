#ifndef OBJECT_H
#define OBJECT_H

#include "tile.h"
#include "tools.h"
#include "path.h"

enum class ObjectInitDir {North = 0, South = 2, East = 3, West = 1};

class Object
{
public:
	Object(int initTilePos, int initTileX, int initTileY, double speed, ObjectInitDir oid) : initTilePos_(initTilePos), initTileX_(initTileX), initTileY_(initTileY), speed_(speed), oid_(oid) {
	}
	virtual void drawAt(double time) = 0;


	void addPathItem(PIDir dir, PIR pir = PIR::Rs);

	//virtual void	addTurnPathItem(PITT pitt, PIR pir, PID pid) = 0;

	void	clearPath() {
		p_.totalLength_ = 0.0d;
		p_.wps_.clear();
	}
protected:
	Path	p_;
	int		initTilePos_;
	int		initTileX_;
	int		initTileY_;
	double	speed_;
	ObjectInitDir oid_;
	double tileDParam_;
	void	addStraightPathItem(PIDir dir);
};

class Human : public Object {
public:
	Human(int initTilePos, int initTileX, int initTileY, double speed, ObjectInitDir oid) : Object(initTilePos, initTileX, initTileY, speed, oid) {
		tileDParam_ = 0.06d;
	}
	virtual void drawAt(double time);
private:
};

class SmallCar : public Object {
public:
	SmallCar(int initTilePos, int initTileX, int initTileY, double speed, ObjectInitDir oid) : Object(initTilePos, initTileX, initTileY, speed, oid) {
		tileDParam_ = 0.32d;
	}
	virtual void drawAt(double time);
private:
};
class LargeCar : public Object {
public:
	LargeCar(int initTilePos, int initTileX, int initTileY, double speed, ObjectInitDir oid) : Object(initTilePos, initTileX, initTileY, speed, oid) {
		tileDParam_ = 0.31d;
	}
	virtual void drawAt(double time);
private:
};

#endif // OBJECT_H
