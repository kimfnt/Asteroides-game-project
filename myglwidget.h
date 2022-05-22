#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include "galaxy.h"
#include "asteroide.h"
#include "vaisseau.h"
#include "station.h"

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    // Constructeur
    MyGLWidget(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent* event);
    void computeMovement(int);

protected:
    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier


    // fonction pour détecter la collision du vaisseau avec un objet
    void checkCollision();

    // fonction pour vérifier que les asteroides ne se chevauchent
    bool overlap(Asteroide*, int);

signals:
    void endOfGame(bool);

private slots:
    void asteroidsChange(int);

private:
    Galaxy* myGalaxy = nullptr;
    Station* maStation=nullptr;
    Asteroide* mesAsteroides=nullptr;
    Vaisseau* monVaisseau=nullptr;

    bool end=false;

    int nombre = 16;

    float placement = 0;
    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;
    int move_ = 0;
    int rot_ = 0;
    float x;
    float r;
    GLfloat vaisseauPos[3] = {0.0, 0.0, 10.0};
    GLfloat cameraFront[3] = {0.0, 0.0, -1.0};
    GLfloat cameraUp[3] = {0.0, 1.0, 0.0};
    GLfloat cameraRight[3];
    GLfloat add[3];
    GLfloat norm;
    GLfloat pitch = 0;
    GLfloat yaw = -90;
};

#endif // MYGLWIDGET_H
