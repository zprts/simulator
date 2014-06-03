#include "camerascontainer.h"

void CamerasContainer::genTab(QTabWidget *w)
{
	w->blockSignals(true);
	w->clear();
	for (Camera c : cameras_) {
        w->addTab(new QWidget(), c.getName());
	}
	w->setCurrentIndex(currentCam);
	w->blockSignals(false);
}
