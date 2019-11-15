#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.numOfParams = argc;
    for (int i = 0; i <argc; i++){
        w.params.push_back(argv[i]);
    }

    return a.exec();
}
