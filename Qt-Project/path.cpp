#include "path.h"
#include <qmath.h>
Path::Path()
{
}
/*
void Path::updateTotalLength()
{
	totalLength_ = 0.0d;
	for (WayPoint wp : wps_) {
		totalLength_ += wp.d_;
	}
}
*/
void Path::walk(double dist)
{
	dist = std::modf(dist, &dist) * totalLength_;
	for (WayPoint wp : wps_) {
		dist = wp.walk(dist);
		if (dist < 0.01d)
			break;
	}
}

double WayPoint::walk(const double &dist)
{
    glRotated(a_, 0.0, 0.0, 1.0);
	if (d_ < 0.0d)
		return dist;

	if (dist > d_)
		glTranslated(d_, 0.0, 0.0);
	else
		glTranslated(dist, 0.0, 0.0);

	return dist - d_;
}
