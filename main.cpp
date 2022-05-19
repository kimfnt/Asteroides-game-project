#include "menuwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    // creation de l'application QT
    QApplication a(argc, argv);
    srand(time(NULL));
    // création de la fenêtre de menu
    MenuWindow w;
    w.show();

    // execution de l'application QT
    return a.exec();
}
