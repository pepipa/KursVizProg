#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwin.h"
#include "help.h"
#include <QMessageBox>
#include <QObject>
#include <QLineEdit>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QPixmap>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

  //  QPixmap pix(":/resource/background.jpg");
   // int w = ui->image123->width();
    //int h = ui->image123->height();

 //   ui->image123->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB5.db");
    if (db.open()) {
        qDebug("open");
    } else {
        qDebug("no open");
    }

    query = new QSqlQuery(db);
    query->exec("PRAGMA foreign_keys = ON;");
    query->exec("CREATE TABLE Jornal( Id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "ФИО TEXT, "
                "Зал TEXT, "
                "Компьютер TEXT, "
                "Дата DATA);");

    model = new QSqlTableModel(this, db);
    model->setTable("Jornal");
    model->select();

    ui->tableView->setModel(model);

    // Установка столбца для сортировки (Id в данном случае)
    int idColumn = model->fieldIndex("Id");
    ui->tableView->sortByColumn(idColumn, Qt::AscendingOrder);

    // Автоматическое изменение размера столбца Id
    ui->tableView->resizeColumnToContents(idColumn);

    int fioColumn = model->fieldIndex("ФИО");
    ui->tableView->resizeColumnToContents(fioColumn);

    // Установите тип данных для каждого столбца с использованием Qt::UserRole
    model->setHeaderData(257, Qt::Horizontal, Qt::UserRole + 1);
    model->setHeaderData(258, Qt::Horizontal, Qt::UserRole + 2);
    model->setHeaderData(259, Qt::Horizontal, Qt::UserRole + 3);
    model->setHeaderData(260, Qt::Horizontal, Qt::UserRole + 4);


    // Установка обработчика сортировки
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::onTableHeaderClicked);


    editForm = new SecondWin();
    editForm->setParent(this, Qt::Window);
    editForm->setModel(model);




    connect(editForm, &SecondWin::UT, this, &MainWindow::UpdateTable);
    editForm2 = new help();
    editForm2->setParent(this, Qt::Window);

    ui->tableView->setModel(model);

    // Установка стиля фона таблицы
    ui->tableView->setStyleSheet("QTableView {"
                                 "background-color: rgb(225, 225, 225);"
                                 "border: 1px solid #d9d9d9;"
                                 "color: #333333;"
                                 "selection-background-color: #0078d4;"
                                 "selection-color: #ffffff;"
                                 "border-radius: 5px;"
                                 "padding: 5px 10px;"
                                 "}");

    // Установка стиля фона верхней строки заголовков
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { "
                                                     "background-color: rgb(225, 225, 225); "
                                                     "border: 1px solid #3498db; "
                                                     "color: #2c2c2c; "
                                                     "border-radius: 5px; "
                                                     "padding: 5px 10px; }");




    connect(ui->lineEditSearch, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);

}

void MainWindow::onSearchTextChanged(const QString &text)
{
    // Вызываем метод фильтрации при изменении текста в строке поиска
    filterTable(text);
}

void MainWindow::filterTable(const QString &filter)
{
    // Фильтруем данные в модели по введенному тексту
    model->setFilter(QString("ФИО LIKE '%%1%'").arg(filter));
    model->select();
}
void MainWindow::on_action_triggered()
{
    QMessageBox::about(this, "О программе", "Версия: 0.1.1 Beta\n\nРазработчик: Трифонов Игнат, ИП-112\n\n            © 2023 уч.год, СибГУТИ");
}
void MainWindow::onTableHeaderClicked(int logicalIndex)
{
    if (logicalIndex >= 0)
    {
        // Определите направление сортировки (по возрастанию или убыванию)
        Qt::SortOrder sortOrder = ui->tableView->horizontalHeader()->sortIndicatorOrder();

        // Установите параметры сортировки в модели
        model->sort(logicalIndex, sortOrder);

        // Вызовите select() для применения сортировки к данным
        model->select();
    }
}



void MainWindow::on_pushButton_3_clicked() // кнопка выхода
{
    //model->submitAll(); // Фиксируем изменения в базе данных
    close();
}

void MainWindow::on_pushButton_2_clicked() // кнопка удаления
{
    model->removeRow(row); // Удалить запись из модели (только из окна вывода)
}



void MainWindow::on_pushButton_4_clicked() // кнопка "Обновить"
{
    model->submitAll(); // Фиксация изменений в базе данных
    model->select(); // Обновление отображения данных
}

void MainWindow::on_pushButton_clicked()
{
    editForm->show();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


void MainWindow::on_commandLinkButton_clicked()
{
    editForm2->show();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateTable()
{
    model->select();
}

void MainWindow::on_pushButton_5_clicked()
{
    editForm3.show();
}

