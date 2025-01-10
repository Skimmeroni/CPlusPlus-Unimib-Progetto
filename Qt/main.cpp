#include "directoryoverwatch.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DirectoryOverwatch w;
    w.show();
    return a.exec();
}
