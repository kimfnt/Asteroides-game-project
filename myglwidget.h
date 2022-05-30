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
    MyGLWidget(QWidget *parent = nullptr);    
    ~MyGLWidget();

    // fonction pour déplacer le vaisseau dans la scène
    void computeMovement(int);

    // fonction pour détecter la collision du vaisseau avec un objet
    void checkCollision();

    // fonction pour vérifier que les asteroides ne se chevauchent
    bool overlap(Asteroide*, int);

protected:
    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent* event);


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
    
    QTimer m_AnimationTimer;
    GLfloat vaisseauPos[3] = {0.0, 2.0, 13.0};
    GLfloat cameraFront[3] = {0.0, 0.0, -1.0};
    GLfloat cameraUp[3] = {0.0, 1.0, 0.0};
    GLfloat add[3];
    GLfloat norm;
    GLfloat pitch = 0;
    GLfloat yaw = -90;

    int state=0;
    int previous_state=0;
    float vitesse = 0.5;
};

#endif // MYGLWIDGET_H
