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
	//double dist = 3.1456d;
	//dist = sin(M_PI_2 / 3.0d);
	//QMessageBox::information(nullptr, "Hi!", QCoreApplication::applicationDirPath() + QString(" --> %1").arg(dist));
	//QString path = QCoreApplication::applicationDirPath();
	//QImage img;
	//img.load(path + "/test.bmp");

	//Camera::MapBg mbg;
	//mbg.init(img);
	//std::vector<std::vector<int>> map = std::vector(img.width(), std::vector<int>(img.height(), 0));
	//int n = 0;
	//Camera::fillColorMap(100, 80, &img, mbg, 1, qRgb(255, 0, 0), n);
	//Camera:: = Camera::genObservation(NULL);
	//auto list = Camera::findCentres(&img, qRgb(255, 0, 0));
	Camera::Observation obs;
	cc_.use();
		obs = cc_.getCurrentCam()->genObservation(Simulation::getInstance());
	cc_.free();

    QVector3D p_;
    //qDebug() << "\npeople:";
	for (auto p : obs.people) {
        //qDebug() << p.rx() << " x " << p.ry();
        p_ = ui->widget->getPos(p.rx(), p.ry());
        addObservation("Human", p_.x(), p_.y());
	}
    //qDebug() << "smallC:";
	for (auto p : obs.smallCars) {
        //qDebug() << p.rx() << " x " << p.ry();
        p_ = ui->widget->getPos(p.rx(), p.ry());
        addObservation("Small Car", p_.x(), p_.y());
	}
    //qDebug() << "largeC:";
	for (auto p : obs.largeCars) {
        //qDebug() << p.rx() << " x " << p.ry();
        p_ = ui->widget->getPos(p.rx(), p.ry());
        addObservation("Large Car", p_.x(), p_.y());
	}
	//QMessageBox::information(nullptr, "Hi!", QCoreApplication::applicationDirPath() + QString(" --> %1 %2").arg(0));
}

void MainWindow::on_pushButton_2_clicked()
{
	//ui->tabWidget->addTab(new QWidget(), "Test");
    cc_.use();
    if(ui->lineEdit->text() == "")
        cc_.cameras_.push_back(Camera());
    else
        cc_.cameras_.push_back(Camera(ui->lineEdit->text()));
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
        //genObservation();
        timerObs = startTimer(1000);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_7->setEnabled(true);
}

void MainWindow::on_pushButton_7_clicked()
{
    killTimer(timerId);
    killTimer(timerObs);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_7->setEnabled(false);
}

void MainWindow::timerEvent(QTimerEvent *timer)
{
    if (timer->timerId() == timerId)
        ui->horizontalSlider->setSliderPosition(static_cast<int>(Simulation::getInstance()->incr_time()*200.0d));
    if (timer->timerId() == timerObs)
        genObservation();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    JsonParser::getInstance()->setFile(fileName);
    ui->pushButton_4->setEnabled(true);
}

void MainWindow::addObservation(QString type, double x, double y)
{
    model->appendRow(new QStandardItem(
                        QString(
                        cc_.getCurrentCam()->getName() + ": " + type +
                        " on pos: " + QString::number(x) +
                        "," + QString::number(y))
                        ));
}

void MainWindow::genObservation()
{
    Camera::Observation obs;
    cc_.use();
        obs = cc_.getCurrentCam()->genObservation(Simulation::getInstance());
    cc_.free();

    QVector3D p_;
    //qDebug() << "\npeople:";
    for (auto p : obs.people) {
        //qDebug() << p.rx() << " x " << p.ry();
        p_ = ui->widget->getPos(p.rx(), p.ry());
        addObservation("Human", p_.x(), p_.y());
    }
    //qDebug() << "smallC:";
    for (auto p : obs.smallCars) {
        //qDebug() << p.rx() << " x " << p.ry();
        p_ = ui->widget->getPos(p.rx(), p.ry());
        addObservation("Small Car", p_.x(), p_.y());
    }
    //qDebug() << "largeC:";
    for (auto p : obs.largeCars) {
        //qDebug() << p.rx() << " x " << p.ry();
        p_ = ui->widget->getPos(p.rx(), p.ry());
        addObservation("Large Car", p_.x(), p_.y());
    }
}
