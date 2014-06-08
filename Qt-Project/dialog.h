#ifndef DIALOG_H
#define DIALOG_H

#include "jsonparser.h"
#include <QDialog>
#include <QStandardItemModel>
namespace Ui {
class Dialog;
}
/*!
 * \brief The Dialog class
 * Okno dialogowe do dodawania nowych obiektów do scenariusza.
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void addPoint(double x, double y);

    QPushButton *getPushButton();
    QStandardItemModel *modelTable;

private slots:
    void on_pushButton_2_clicked();
    void on_buttonBox_accepted();


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_HPP
