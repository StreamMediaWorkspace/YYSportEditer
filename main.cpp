#include "MainWindow.h"

#include <QApplication>
#include "PlayerDemo.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	PlayerDemo w;
	w.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
