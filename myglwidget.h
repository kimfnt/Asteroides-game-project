#include "asteroide.h"
#include "galaxy.h"
#include "vaisseau.h"
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>

// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget
{
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

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    //Asteroide* myAsteroide={nullptr};
    Galaxy* myGalaxy=nullptr;
    Vaisseau* monVaisseau=nullptr;
    //int number = 16;
    float placement = 0;
    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;
    int move_ = 0;
    int rot_ = 0;
    float x;
    float r;
    GLfloat vaisseauPos[3] = {0.0, 0.0, 3.0};
    GLfloat cameraFront[3] = {0.0, 0.0, -1.0};
    GLfloat cameraUp[3] = {0.0, 1.0, 0.0};
    GLfloat cameraRight[3];
    GLfloat add[3];
    GLfloat norm;
    GLfloat pitch = 0;
    GLfloat yaw = -90;
};
