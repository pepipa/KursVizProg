#include "raspisanie.h"
#include "ui_raspisanie.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

raspisanie::raspisanie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::raspisanie)
{
    ui->setupUi(this);
    model = new QStandardItemModel(6, 5, this);
    setupTable();
    currentFileName = "data.txt";
    loadTableData();

    connect(ui->pushButton, &QPushButton::click, this, &raspisanie::on_pushButton_clicked);
    connect(ui->pushButton_4, &QPushButton::click, this, &raspisanie::on_pushButton_4_clicked); // Подключаем кнопку сохранения

}

raspisanie::~raspisanie()
{
    delete ui;
}

void raspisanie::setupTable()
{
    QStringList daysOfWeek = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница"};

                               model->setHorizontalHeaderLabels(daysOfWeek);

    ui->tableView->setModel(model); // Привязываем модель к таблице
}

void raspisanie::on_pushButton_2_clicked() // кнопка выхода
{
    close();
}

void raspisanie::on_pushButton_clicked()
{
    saveTableData();
}

void raspisanie::loadTableData()
{
    // Создаем объект QSettings для чтения данных из файла
    QSettings settings("myapp", "raspisanie");

    // Восстанавливаем значения ячеек таблицы из настроек
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QString key = QString("Cell_%1_%2").arg(row).arg(column);
            QString cellValue = settings.value(key).toString();
            QModelIndex index = model->index(row, column);
            model->setData(index, cellValue, Qt::DisplayRole);
        }
    }
}

void raspisanie::saveTableData()
{
    // Создаем объект QSettings для сохранения данных в файл
    QSettings settings("myapp", "raspisanie");

    // Перебираем ячейки таблицы и записываем их значения в настройки
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QModelIndex index = model->index(row, column);
            QString cellValue = model->data(index, Qt::DisplayRole).toString();
            QString key = QString("Cell_%1_%2").arg(row).arg(column);

            settings.setValue(key, cellValue);
        }
    }

    // Создаем объект QFile для сохранения данных в текстовый файл
    QFile file(currentFileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Перебираем ячейки таблицы и записываем их значения в файл
        for (int row = 0; row < model->rowCount(); ++row) {
            for (int column = 0; column < model->columnCount(); ++column) {
                QModelIndex index = model->index(row, column);
                QString cellValue = model->data(index, Qt::DisplayRole).toString();

                // Определяем фиксированную ширину ячейки (например, 15 символов)
                int cellWidth = 15;

                // Дополняем текст пробелами до фиксированной ширины, чтобы выровнять по первой букве
                cellValue = cellValue.leftJustified(cellWidth, ' ');

                out << cellValue;

                if (column < model->columnCount() - 1) {
                    out << "\t"; // Используем табуляцию для разделения значений, кроме последней ячейки в строке
                }
            }
            out << "\n"; // Переходим на новую строку после каждой строки таблицы
        }

        // Закрываем файл после записи данных
        file.close();

        QMessageBox::information(this, "Запись данных", "Данные записаны в файл", "Ок");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи", "Ок");
    }
}


void raspisanie::on_pushButton_4_clicked()
{
    QString selectedFileName;
    QString previousFileName = currentFileName;

    QSettings settings("myapp", "raspisanie");

    if (settings.contains("previousFileName")) {
        previousFileName = settings.value("previousFileName").toString();
    }

    // Выводим диалог только если предыдущий путь не пустой
    if (!previousFileName.isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение", "Хотите сохранить по предыдущему пути?\n\n" + previousFileName,
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            selectedFileName = previousFileName;
        }
    }

    // Если пользователь выбрал "Нет" или предыдущего пути не было, открываем диалог сохранения
    if (selectedFileName.isEmpty()) {
        QFileDialog fileDialog(this);
        fileDialog.setFileMode(QFileDialog::AnyFile);
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setNameFilter("Текстовые файлы (*.txt);;Все файлы (*)");

        if (fileDialog.exec()) {
            selectedFileName = fileDialog.selectedFiles().first();
            settings.setValue("previousFileName", selectedFileName);
        }
    }

    // Если выбран какой-то путь, сохраняем данные и выводим сообщение
    if (!selectedFileName.isEmpty()) {
        currentFileName = selectedFileName;
        saveTableData();

        QFileInfo fileInfo(currentFileName);
        QString fullPath = fileInfo.absoluteFilePath();

        QFile file(currentFileName);
        if (file.exists()) {
            QMessageBox::information(this, "Сохранение файла", "Файл успешно сохранен по пути:\n" + fullPath, "Ок");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл", "Ок");
        }
    }
}
