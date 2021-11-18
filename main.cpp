
#include "mainwindow.h"

#include <QApplication>
#include <QApplication>
#include <QFile>
#include <QString>
#include <QLatin1String>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
