#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	cc_.use();
		cc_.cameras_.push_back(Camera("Main camera"));
		cc_.currentCam = 0;
		cc_.genTab(ui->tabWidget);
	cc_.free();
	connect(&timer_, SIGNAL(timeout()), ui->widget, SLOT(updateGL()));
	timer_.start(25);
	connect(ui->widget, SIGNAL(statusEvent(QString)), this, SLOT(setStatusBarText(QString)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	double dist = 3.1456d;
	dist = sin(M_PI_2 / 3.0d);
	QMessageBox::information(nullptr, "Hi!", QCoreApplication::applicationDirPath() + QString(" --> %1").arg(dist));

}

void MainWindow::on_pushButton_2_clicked()
{
	//ui->tabWidget->addTab(new QWidget(), "Test");
	cc_.use();
		cc_.cameras_.push_back(Camera());
		cc_.currentCam = cc_.cameras_.size() - 1;
		cc_.genTab(ui->tabWidget);
	cc_.free();
	//img.save("testcam.jpg");
}

void MainWindow::setStatusBarText(const QString &msg)
{
	ui->statusBar->showMessage(msg);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
	cc_.use();
		cc_.currentCam = index;
	cc_.free();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
	Simulation::getInstance()->setSimulationTime(static_cast<double>(value)/200.0d);
}
