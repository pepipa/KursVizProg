#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QtWidgets>

void loadModules(QSplashScreen* psplash){
    QElapsedTimer time;
    time.start();

    for (int i = 0; i < 100; ) {
        if (time.elapsed() > 20) {
            time.start();
            ++i;
        }

        psplash->showMessage("\n\nЗагрузка...: "
                                 + QString::number(i) + "%",
                             Qt::AlignBottom | Qt::AlignHCenter, // Теперь выравнивание внизу
                             Qt::black
                             );
        qApp->processEvents();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Загрузка изображения
    QPixmap originalPixmap("D:\\Qt\\Curs\\Jurnal22\\comp.png");

    // Проверка на успешную загрузку
    if (originalPixmap.isNull()) {
        qDebug() << "Failed to load image";
        return -1;
    }

    // Уменьшение размера изображения
    QSize newSize(200, 200); // Новый размер изображения
    QPixmap scaledPixmap = originalPixmap.scaled(newSize, Qt::KeepAspectRatio);

    // Создание вступительного экрана с уменьшенным изображением
    QSplashScreen splash(scaledPixmap);
    splash.show();

    MainWindow w;
    loadModules(&splash);
    splash.finish(&w);
    w.show();

    return a.exec();
}
