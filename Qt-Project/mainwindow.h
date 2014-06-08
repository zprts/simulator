#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGLWidget>
#include <QTimer>
#include "camerascontainer.h"
#include "dialog.h"
#include <QStandardItemModel>

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

    void on_pushButton_4_clicked();

    void on_pushButtonDialog_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

public slots:
        void setStatusBarText(const QString &msg);

private:
	Ui::MainWindow *ui;
	QTimer timer_;
	CamerasContainer &cc_ = CamerasContainer::getInstance();
    Dialog dialog_;
    QStandardItemModel *model;

    void update();

    int timerId;
    int timerObs;
    void timerEvent(QTimerEvent *timer);
    void addObservation(QString type, double x, double y);
    void genObservation();
};

#endif // MAINWINDOW_H
