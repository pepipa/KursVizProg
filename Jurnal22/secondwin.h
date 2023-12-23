#ifndef SECONDWIN_H
#define SECONDWIN_H

#include <QDialog>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>


namespace Ui {
class SecondWin;
}

class SecondWin : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWin(QWidget *parent = nullptr);
    ~SecondWin();
    //QDataWidgetMapper* mapper;
    QSqlDatabase db;
    QSqlQuery *query;

    QSqlTableModel    *model;
    QSqlTableModel    *model2;

    void setModel(QAbstractItemModel* model);




private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();



private:
    Ui::SecondWin *ui;

signals:
    void UT();
};

#endif // SECONDWIN_H
