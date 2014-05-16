#include "path.h"
#include <qmath.h>
Path::Path()
{
}

void Path::addTurnPathItem(PIDir pid, PIR pir, double tileDParam)
{
	double d = 1.0d - tileDParam;
	if (pir == PIR::Rs)
		d = tileDParam;
	const int n = 15;
	d = d*sqrt(2*(1 - cos(M_PI_2/n)));
	double a = ((pid == PIDir::Right)?(-1.0d):(1.0d)) * 90.0d / static_cast<double>(n);
	for (int i = 0; i < n; i++) {
		wps_.push_back(WayPoint(d, a * ((i==0)?(0.5d):(1.0d))));
	}
	wps_.push_back(WayPoint(-1.0d, a * 0.5d));
	totalLength_ += d * n;
}

void Path::updateTotalLength()
{
	totalLength_ = 0.0d;
	for (WayPoint wp : wps_) {
		totalLength_ += wp.d_;
	}
}

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
