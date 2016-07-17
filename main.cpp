#include "MainControl.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainControl w;
    w.show();

    return a.exec();
}
