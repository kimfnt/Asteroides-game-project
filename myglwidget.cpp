#include "myglwidget.h"
#include <QApplication>
#include <cmath>
#include <algorithm>


// Declarations des constantes
const unsigned int WIN = 800;

// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN, WIN);

    // Connexion du timer
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += 1.0f;
        update();
    });

    m_AnimationTimer.setInterval(20);
    m_AnimationTimer.start();
}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.5f, 0.8f, 0.9f, 0.0f);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
    myGalaxy=new Galaxy();
}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        gluPerspective(70,1,0.1, 2000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Fonction d'affichage
void MyGLWidget::paintGL()
{
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definition de la position de la camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0.0f, 4.f, 4.f, 0.0f, 0.0f, 0.f, 0.0f, 1.0f, 0.0f);
    gluLookAt(0.0f, 4.0f, 10.1f,
              0.0f, 0.0f, 0.f,
              0.0f, 1.0f, 0.0f);

    //glDisable(GL_LIGHTING); // on désactive le lighting pour dessiner la route

    //glEnable(GL_LIGHTING); // on réactive le lighting par la suite


    // translation des éléments suivants (voiture, roues, phares) sur l'axe x
    //glTranslatef(placement, 0.f, 0.f);

    myGalaxy->Display();

}


