#include <QApplication>
#include "myglwidget.h"

int main(int argc, char *argv[])
{
    // Creation de l'application QT
    QApplication app(argc, argv);
    srand (time(NULL));
    // Creation du widget opengl
    MyGLWidget glWidget;
    glWidget.show();

    // Execution de l'application QT
    return app.exec();
}
