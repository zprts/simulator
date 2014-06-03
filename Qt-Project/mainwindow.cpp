#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsonparser.h"

#include <QMessageBox>
#include <QFileDialog>

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
    connect(dialog_.getPushButton(), SIGNAL(clicked()), this, SLOT(on_pushButtonDialog_clicked()));
    model = new QStandardItemModel(this);
    ui->listView->setModel(model);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
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


void MainWindow::on_pushButtonDialog_clicked()
{
    //QMessageBox msgBox;
    //msgBox.setText("Set point on window");
    //msgBox.exec();


    ui->widget->setDialog(&dialog_);
    ui->widget->setAddPointMode(true);
    //dialog_.setModal(false);
    this->setWindowModality(Qt::ApplicationModal);
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

void MainWindow::on_pushButton_4_clicked()
{
    dialog_.show();
    //ui->horizontalSlider->setSliderPosition(200);
    //dialog_.setModal(true);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    JsonParser::getInstance()->readJson(fileName);
    ui->pushButton_3->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
        timerId = startTimer(100);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_7->setEnabled(true);
}

void MainWindow::on_pushButton_7_clicked()
{
    killTimer(timerId);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_7->setEnabled(false);
}

void MainWindow::timerEvent(QTimerEvent *timer)
{
    ui->horizontalSlider->setSliderPosition(static_cast<int>(Simulation::getInstance()->incr_time()*200.0d));
}

void MainWindow::on_pushButton_6_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    JsonParser::getInstance()->setFile(fileName);
    ui->pushButton_4->setEnabled(true);
}
