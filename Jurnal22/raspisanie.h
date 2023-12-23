#ifndef RASPISANIE_H
#define RASPISANIE_H

#include <QSettings>
#include <QFile>
#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class raspisanie;
}

class raspisanie : public QDialog
{
    Q_OBJECT

public:
    explicit raspisanie(QWidget *parent = nullptr);
    ~raspisanie();
    void setupTable();
    void loadTableData();
    void saveTableData();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked(); // Добавляем слот для кнопки "Четная неделя"
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_buttonBox2_accepted();

private:
    Ui::raspisanie *ui;
    QStandardItemModel *model;
    QString currentFileName;
};

#endif // RASPISANIE_H
