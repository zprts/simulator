#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGLWidget>
#include <QTimer>
#include "camerascontainer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_tabWidget_currentChanged(int index);

	void on_horizontalSlider_valueChanged(int value);

public slots:
		void setStatusBarText(const QString &msg);

private:
	Ui::MainWindow *ui;
	QTimer timer_;
	CamerasContainer &cc_ = CamerasContainer::getInstance();
};

#endif // MAINWINDOW_H
