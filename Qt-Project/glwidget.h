#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMessageBox>
#include <GL/glu.h>
#include <QTimer>
#include <QMouseEvent>
#include "city.h"
#include "camera.h"
#include "simulation.h"
#include "camerascontainer.h"
#include "dialog.h"

#include <QStandardItemModel>

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit GLWidget(QWidget *parent = 0);
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);


    void setDialog(Dialog *d);
    void setAddPointMode(bool mode);
    QVector3D   getPos ( int posX, int posY );
    //public slots:
        void test();

    signals:
        void statusEvent(const QString &msg);

private:
    QPoint			point_{};
	CamerasContainer &cc_;
	void	mouseMoveEvent ( QMouseEvent * event );
    void	mousePressEvent ( QMouseEvent * event );

    bool addPointMode = false;

    Dialog *d_;
};


#endif // GLWIDGET_H
