#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QPushButton *getPushButton();
    //QStandardItemModel *getModelList();

    void addPoint(double x, double y);

    QStandardItemModel *modelList;
private slots:
	void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_HPP
