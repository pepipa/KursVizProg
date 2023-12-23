#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include "secondwin.h"
#include "help.h"
#include "raspisanie.h"
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void UpdateTable();
    void onTableHeaderClicked(int logicalIndex);

private slots:
    void onSearchTextChanged(const QString &text);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_commandLinkButton_clicked();


private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    SecondWin* editForm;
    help* editForm2;
    SecondWin *A;
    raspisanie editForm3;
    int row;
    QDataWidgetMapper* mapper;

    void filterTable(const QString &filter);
};

#endif // MAINWINDOW_H
