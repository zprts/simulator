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
	connect(dialog_.getPushButton(), SIGNAL(clicked()), this, SLOT(pushButtonDialog_clicked()));
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
/*!
 * \brief MainWindow::on_pushButton_2_clicked
 * Tworzy nową kamerę o podanej nazwie, jeżeli nazwa jest pustym napisem,
 * tworzona jest kamera o domyślnej nazwie.
 */
void MainWindow::on_pushButton_2_clicked()
{
    cc_.use();
    if(ui->lineEdit->text() == "")
        cc_.cameras_.push_back(Camera());
    else
        cc_.cameras_.push_back(Camera(ui->lineEdit->text()));
        cc_.currentCam = cc_.cameras_.size() - 1;
        cc_.genTab(ui->tabWidget);
    cc_.free();
}

void MainWindow::setStatusBarText(const QString &msg)
{
	ui->statusBar->showMessage(msg);
}

/*!
 * \brief MainWindow::on_pushButtonDialog_clicked
 * Pobiera informację z okna dialogowego i uruchamia tryb, wktórym użytkownik może wskazać
 * punkt na widgetie potrzebny do zamodelowania ruchu obiektu.
 */
void MainWindow::pushButtonDialog_clicked()
{
    ui->widget->setDialog(&dialog_);
    ui->widget->setAddPointMode(true);
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
/*!
 * \brief MainWindow::on_pushButton_4_clicked
 * Pokazuje okno dialogowe, za pomocą którego można dodawać nowe obiekty do pliku ze scenariuszem.
 */
void MainWindow::on_pushButton_4_clicked()
{
    dialog_.show();
}
/*!
 * \brief MainWindow::on_pushButton_5_clicked
 * Otwierane jest okno do wyboru pliku ze scenariuszem. Po wczytaniu pliku można rozpocząć symulację.
 */
void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    JsonParser::getInstance()->readJson(fileName);
    ui->pushButton_3->setEnabled(true);
}
/*!
 * \brief MainWindow::on_pushButton_3_clicked
 * Rozpoczyna się symulacja, uruchamiane są timery do przesuwania suwaka i generowania obserwacji.
 */
void MainWindow::on_pushButton_3_clicked()
{
        timerSlider = startTimer(100);
        timerObs = startTimer(1000);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_7->setEnabled(true);
}
/*!
 * \brief MainWindow::on_pushButton_7_clicked
 * Zatrzymywanie symulacji.
 */
void MainWindow::on_pushButton_7_clicked()
{
    killTimer(timerSlider);
    killTimer(timerObs);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_7->setEnabled(false);
}

void MainWindow::timerEvent(QTimerEvent *timer)
{
    if (timer->timerId() == timerSlider)
        ui->horizontalSlider->setSliderPosition(static_cast<int>(Simulation::getInstance()->incr_time()*200.0d));
    if (timer->timerId() == timerObs)
        genObservation();
}
/*!
 * \brief MainWindow::on_pushButton_6_clicked
 * Otwierane jest okno do wyboru pliku w którym mają być zapisywane dane scenariusza.
 * Po wyborze pliku można dodawać nowe obiekty.
 */
void MainWindow::on_pushButton_6_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    JsonParser::getInstance()->setFile(fileName);
    ui->pushButton_4->setEnabled(true);
}
/*!
 * \brief MainWindow::addObservation
 * Dodaje pojedyńczą obserwację w formie loga na ekranie.
 * \param type typ obiektu
 * \param x współrzędna x
 * \param y współrzędna y
 */
void MainWindow::addObservation(QString type, double x, double y)
{
    model->appendRow(new QStandardItem(QString(cc_.getCurrentCam()->getName() + ": " + type +
                        " on pos: " + QString::number(x) + "," + QString::number(y))));
}
/*!
 * \brief MainWindow::genObservation
 * Generuje obserwację o widocznych obiektach.
 */
void MainWindow::genObservation()
{
    Camera::Observation obs;
    cc_.use();
        obs = cc_.getCurrentCam()->genObservation(Simulation::getInstance());
    cc_.free();

    QVector3D p_;
    for (auto p : obs.people) {
        p_ = ui->widget->getPos(p.rx(), p.ry());
        addObservation("Human", p_.x(), p_.y());
    }
    for (auto p : obs.smallCars) {
        p_ = ui->widget->getPos(p.rx(), p.ry());
        addObservation("Small Car", p_.x(), p_.y());
    }
    for (auto p : obs.largeCars) {
        p_ = ui->widget->getPos(p.rx(), p.ry());
        addObservation("Large Car", p_.x(), p_.y());
    }
}
