#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QtCore/qmath.h>
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
    QVector3D	pos_ = {0.0, 0.0, 1.1};
	QVector3D	step_;
	qreal		angleXY_ = 0.0;
	qreal		angleZ_ = -M_PI_2*0.3f;
	QString		name_;
    enum {IMG_HEIGHT = 128, IMG_WIDTH = 128};
    //default image size
    //DELETE: potrzebuje tego anuma, bo inaczej
    //przekazywanie 2d tablicy o nieznanych wymiarach sie wykrzacza

    void fillColorMap(int x, int y,
                      QImage *img,
                      int color_map[IMG_WIDTH][IMG_HEIGHT],
                      int area_number,
                      QRgb color,
                      int* pxl_number);

    std::vector<std::pair<int, int> > findCentres(QImage *img, QRgb color);
};

#endif // CAMERA_H
