#ifndef PATH_H
#define PATH_H

#include <QGLWidget>
#include "tools.h"
#include <cmath>

class Object;

enum class PIDir	{Forward = 0, Left = 1, Backward = 2, Right = 3};
enum class PIR		{Rs = 0, Rl = 1};

class WayPoint {	//I really hope that eps of d_ and a_ won't be critical...
public:
	WayPoint(double d = 0.0d, double a = 0.0d) : d_(d), a_(a) {
	}
	double	d_;
	double	a_;

	double	walk(const double &dist);
};

class Path
{
	friend class Object;
public:
	Path();

	QVector<WayPoint> wps_;

	void	updateTotalLength();
	double	getTotalLength() {
		return totalLength_;
	}
	void	walk(double dist);
private:
	double	totalLength_;
};

#endif // PATH_H
