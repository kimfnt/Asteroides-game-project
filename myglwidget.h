#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include "asteroide.h"
#include "galaxy.h"

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    // Constructeur
    MyGLWidget(QWidget *parent = nullptr);

protected:
    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

private slots:
    void asteroidsChange(int);

private:
    Galaxy* myGalaxy=nullptr;
    float placement = 0;
    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;
    int number;
};

#endif // MYGLWIDGET_H
