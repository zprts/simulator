#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QtCore/qmath.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "city.h"
#include "simulation.h"


class Camera
{
public:
	Camera(QString name = "cam") : name_(name) {
		step_[0] = qCos(angleZ_)*qCos(angleXY_);
		step_[1] = qCos(angleZ_)*qSin(angleXY_);
		step_[2] = qSin(angleZ_);
	}
	void		lookAt();

	void		rotate(QPoint p);
	void		moveXY(QPoint p);
	void		distance(QPoint p);

	void		genView(Simulation *sim);
	QImage		genImage(Simulation *sim);
	void		genObservation(Simulation *sim); // <--TODO TODO TODO !!! return type ought to be an Observation... should use genImage inside

	QString		getName() {
		return name_;
	}
	void		setName(QString name) {
		name_ = name;
	}
private:
    cv::Mat     QImage2Mat(QImage const& src);
	QVector3D	pos_ = {0.0, 0.0, 0.1};
	QVector3D	step_;
	qreal		angleXY_ = 0.0;
	qreal		angleZ_ = -M_PI_2*0.3f;
	QString		name_;
};

#endif // CAMERA_H
