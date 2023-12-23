#include "secondwin.h"
#include "ui_secondwin.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

SecondWin::SecondWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWin)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB5.db");
    if(db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("no open");
    }



    model = new QSqlTableModel(this, db);
    model->setTable("Jornal");
    model->select();



    //mapper = new QDataWidgetMapper(this);

}

SecondWin::~SecondWin()
{
    delete ui;
}

void SecondWin::setModel(QAbstractItemModel* /*model*/)
{
    //mapper->setModel(model);
    //mapper->addMapping(ui->comboBox,1);
}

void SecondWin::on_pushButton_clicked()
{
    QSqlQuery query;
    //QString snumber1;
    QString number1;
    QString number2;
    QString number3;
    QString number4;
    //   QString number5;

    //QString snumber2;
    number1 = ui->comboBox->currentText();
    number2 = ui->lineEdit_5->text();
    number4 = ui->dateEdit->text();
    //   number5 = ui->dateEdit->text();
    number3 = ui->comboBox_2->currentText();


    // int number2 = ui->lineEdit_2->text().toInt();
    // snumber1 = QString::number(number1);;
    //snumber2 = QString::number(number2);;
    if(number2 == "")
    {QMessageBox::information(this, "Внимание", "Заполните пустые поля.", "Понял");}
    else if (number2.toInt()) {
        QMessageBox::information(this, "Внимание", "Введите ФИО, а не число.", "Понял");
    }
    else{
        qDebug() << "Cработало";
        query.prepare("INSERT INTO Jornal (ФИО, Зал, Компьютер, Дата) VALUES (:FName, :Class, :Pred, :Date)");

        query.bindValue(":Class", number1);
        query.bindValue(":FName", number2);
        query.bindValue(":Pred", number3);
        query.bindValue(":Date", number4);
        //    query.bindValue(":Date", number5);



        if(!query.exec()){
            qDebug() << "error add";
        }
        emit UT();

        model->setTable("Jornal");
        model->select();
        QMessageBox::information(this, "Сохранение", "Сохранено.", "Ок");
        ui->lineEdit_5->clear();

        close();
    }
}

void SecondWin::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Внимание", "Вы хотите вернуться в меню?",
                                  QMessageBox::Yes |QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        ui->lineEdit_5->clear();


        this->close();

    }
}

void SecondWin::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Внимание", "Вы действительно хотите сбросить значения?",
                                  QMessageBox::Yes |QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ui->lineEdit_5->clear();


    }
    QMessageBox::information(this, "Сброс", "Поля сброшены.", "Принял");


}


