#include "dialog.h"
#include "ui_dialog.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <jsonparser.h>
#include <mainwindow.h>

#include <QJsonDocument>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    modelList = new QStandardItemModel(this);
    QStringList listLabel;
    listLabel << "coord x" << "coord y" << "time";
    modelList->setHorizontalHeaderLabels(listLabel);

    ui->tableView->setModel(modelList);
    //this->setModal(true);
    //listWidget = new QListWidget(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{//modelList->appendRow(new QStandardItem(QString::number(3)+"\tcat"));
    /*QStandardItemModel *stdModel = new QStandardItemModel(this);
    double x = 3.0d;
    stdModel->appendRow(list);

    ui->listView->setModel(stdModel);
    ui->listView->repaint();*/
  //  QDialogBox msgBox;
  //  msgBox.setText("Set point on window");
  //  msgBox.exec();
    //QStandardItemModel *modelList;
    //modelList = new QStandardItemModel(this);
    this->setWindowModality(Qt::NonModal);
}

QPushButton *Dialog::getPushButton() {
    return ui->pushButton;
}

//QStandardItemModel *Dialog::getModelList() {
  //  return modelList;
//}

void Dialog::addPoint(double x, double y)
{
    //QStandardItemModel *lList = modelList;
    //modelList = new QStandardItemModel(this);
    //ui->listView->setModel(NULL);
    //static_cast<QStandardItemModel *>(ui->listView->model())->appendRow(new QStandardItem(QString::number(x)+"\tcat"));
    //ui = new Ui::Dialog;
    //Dialog::ui->retranslateUi(this);
    QList<QStandardItem *> list;
    list.append(new QStandardItem(QString::number(x)));
    list.append(new QStandardItem(QString::number(y)));
    modelList->appendRow(list);


    //modelList->removeRow(ui->tableView->currentIndex().row());
    //modelList->setItem(0,0,new QStandardItem(QString::number(x)));
    //modelList->setItem(0,1,new QStandardItem(QString::number(y)));

}

void Dialog::on_pushButton_2_clicked()
{
    modelList->removeRow(ui->tableView->currentIndex().row());
}



void Dialog::on_buttonBox_accepted()
{
    JsonParser::getInstance()->addObject(ui->comboBox->currentText(), modelList);
    while (modelList->rowCount() > 0)
        modelList->removeRow(0);
}

void Dialog::setModal(bool modal)
{
    if (modal)
        this->setWindowModality(Qt::ApplicationModal);
    else
        this->setWindowModality(Qt::NonModal);
    //ui->tableWidget->
}
