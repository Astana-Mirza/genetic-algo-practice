#include <gui/main_window.h>

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("genetic_algorithm_ru_RU");
    a.installTranslator(&translator);
    MainWindow w;
    w.show();
    return a.exec();
}
