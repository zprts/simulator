#ifndef CAMERASCONTAINER_H
#define CAMERASCONTAINER_H

#include "camera.h"
#include <QMutex>
#include <QTableWidget>

class CamerasContainer
{
public:
	static CamerasContainer &getInstance() {
		static CamerasContainer c;
		return c;
	}
	QVector<Camera> cameras_;
	int				currentCam = -1;
	void use() {
		m_.lock();
	}
	void free() {
		m_.unlock();
	}
	bool currentCamValid() {
		if (currentCam < 0)
			return false;
		return true;
	}
	Camera *getCurrentCam() {
		return &cameras_[currentCam];
	}
	void genTab(QTabWidget *w);
private:
	QMutex	m_;
	CamerasContainer() {}
};

#endif // CAMERASCONTAINER_H
