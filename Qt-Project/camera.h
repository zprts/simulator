#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QtCore/qmath.h>
#include "city.h"
#include "simulation.h"
#include <vector>


class Camera
{
public:
	Camera(QString name = "cam") : name_(name) {
		step_[0] = qCos(angleZ_)*qCos(angleXY_);
		step_[1] = qCos(angleZ_)*qSin(angleXY_);
		step_[2] = qSin(angleZ_);
	}
	class MapBg : public std::vector<std::vector<int>> {
	public:
		void init(QImage *img) {
			init(img->width(), img->height());
		}
		void init(int w, int h) {
			clear();
			resize(w, vector<int>(h, 0));
		}
	};
	struct Observation {
		std::vector<QPoint> people, smallCars, largeCars;
	};
	void		lookAt();

	void		rotate(QPoint p);
	void		moveXY(QPoint p);
	void		distance(QPoint p);

	void		genView(Simulation *sim);
	QImage		genImage(Simulation *sim);
	Observation genObservation(Simulation *sim);

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

public:
	static void fillColorMap(int x, int y,
					  QImage *img,
					  MapBg &mapBg,
					  int area_number,
					  QRgb color,
					  int &pxl_number);

	static std::vector<QPoint> findCentres(QImage *img, QRgb color);
};

#endif // CAMERA_H
