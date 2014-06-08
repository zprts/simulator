#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    modelTable = new QStandardItemModel(this);
    QStringList listLabel;
    listLabel << "coord x" << "coord y";
    modelTable->setHorizontalHeaderLabels(listLabel);
    ui->tableView->setModel(modelTable);
}

Dialog::~Dialog()
{
    delete ui;
}

QPushButton *Dialog::getPushButton() {
    return ui->pushButton;
}
/*!
 * \brief Dialog::addPoint
 * Dodaje punkt do tabeli
 * \param x współrzędna x
 * \param y współrzędna y
 */
void Dialog::addPoint(double x, double y)
{
    QList<QStandardItem *> list;
    list.append(new QStandardItem(QString::number(x)));
    list.append(new QStandardItem(QString::number(y)));
    modelTable->appendRow(list);
}
/*!
 * \brief Dialog::on_pushButton_2_clicked
 * Usuwa wskazany wierz z tabeli
 */
void Dialog::on_pushButton_2_clicked()
{
    modelTable->removeRow(ui->tableView->currentIndex().row());
}
/*!
 * \brief Dialog::on_buttonBox_accepted
 * Dodaje nowo utworzony do pliku w formacie json oraz usuwa wszystkie
 * tabeli z punktami
 */
void Dialog::on_buttonBox_accepted()
{
    JsonParser::getInstance()->addObject(ui->comboBox->currentText(), ui->lineEdit->text().toDouble(), modelTable);
    while (modelTable->rowCount() > 0)
        modelTable->removeRow(0);
}

