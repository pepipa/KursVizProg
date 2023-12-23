#include "help.h"
#include "ui_help.h"
#include <QScrollBar>
#include <QScrollArea>
#include <QVBoxLayout>


help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);

    QString helpText = "\n\t\tРуководство пользователя\n\n"
                       "\tУчет посещения компьютерного клуба\n\n"
                       "\t\tНачало работы:\n"
                       "\tЧтобы создать запись посещения клиента,\n"
                       "\tкликнете мышкой по кнопке \"Добавить\". После этого\n"
                       "\tоткроется окно добавление клиента в таблицу. \n"
                       "\tВ открывшемся окне: \n\tможно написать информацию о человеке. После, \n\tнажать кнопку \"Cохранить\", чтобы сохранить информацию, \n\tи кнопку \"Ок\", чтобы подтвердить свои действия.\n\n"
                       "\t\tРедактирование записей:\n"
                       "\tВы можете изменить каждый из столбцов,\n"
                       "\tдля этого нужно кликнуть мышкой на нужную вам ячейку, \n\tвписать значение и нажать кнопку \"Enter.\"\n\n"
                       "\t\tУдаление записей:\n"
                       "\tДля удаления записи в панеле меню таблице,\n"
                       "\tкликнуть мышкой по любой ячейке записи, \n\tкоторую вы хотите удалить\n"
                       "\t\tСортировка таблицы по столбцу:\n"
                       "\tНажатием на заголовок столбца сортируется столбец,\n\tтекстовый от А до Я и наоборот при нажатии второй раз,\n\tчисловой от самого маленького числа до самого большого\n";

    // Установка текста в QLabel
    ui->label->setText(helpText);

    // Добавление QScrollArea вокруг QLabel
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true); // Делаем QScrollArea растягиваемым

    // Устанавливаем QLabel в QScrollArea
    scrollArea->setWidget(ui->label);

    // Устанавливаем QScrollArea в макет
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(scrollArea);

    // Устанавливаем макет в основное окно
    setLayout(layout);
}

help::~help()
{
    delete ui;
}
