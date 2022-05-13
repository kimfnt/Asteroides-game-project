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
    monVaisseau=new Vaisseau();
    x = 0;
    r = 0;
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
//    gluLookAt(cameraPos[0],cameraPos[1],cameraPos[2],
//              cameraPos[0]+cameraFront[0],cameraPos[1]+cameraFront[1],cameraPos[2]+cameraFront[2],
//              cameraUp[0],cameraUp[1],cameraUp[2]);
    gluLookAt(vaisseauPos[0]-cameraFront[0],vaisseauPos[1]-cameraFront[1],vaisseauPos[2]-cameraFront[2],
              vaisseauPos[0],vaisseauPos[1],vaisseauPos[2],
              cameraUp[0],cameraUp[1],cameraUp[2]);
    //coord cartésiennes -> sphériques
    // z = p*sin(teta)*cos(phi)
    // x = p*sin(teta)*sin(phi)
    // y = p*cos(teta)

    //coord sphériques -> cartésiennes
    // p = sqrt(x^2 + y^2 + z^2)
    // teta = arccos(y/p)
    // phi = arctan(x/z)

    myGalaxy->Display();

//Placer le vaisseau
    glTranslatef(vaisseauPos[0],vaisseauPos[1],vaisseauPos[2]);
    glRotatef(-yaw-90,0.0,1.0,0.0);
    glRotatef(pitch+10,1.0,0.0,0.0);
    glScaled(0.05,0.05,0.05);
    glPushMatrix();
    monVaisseau->Display(0);
    glPopMatrix();

    /*
     * Je crois que j'ai pas besoin de ça mais au cas où je le garde ici ça me parait chelou
    cameraRight[0] = cameraUp[1]*cameraFront[2]-cameraUp[2]*cameraFront[1];
    cameraRight[1] = cameraUp[2]*cameraFront[0]-cameraUp[0]*cameraFront[2];
    cameraRight[2] = cameraUp[0]*cameraFront[1]-cameraUp[1]*cameraFront[0];
    norm = sqrt(cameraRight[0]*cameraRight[0]+cameraRight[1]*cameraRight[1]+cameraRight[2]*cameraRight[2]);
    cameraRight[0] = cameraRight[0]/norm;
    cameraRight[1] = cameraRight[1]/norm;
    cameraRight[2] = cameraRight[2]/norm;
    glRotatef(-yaw-90,cameraUp[0],cameraUp[1],cameraUp[2]);
    glRotatef(-pitch,cameraRight[0],cameraRight[1],cameraRight[2]);
*/

}

// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    // Cas par defaut
    default:
    {
        // Ignorer l'evenement
        event->ignore();
        return;
    }
    case Qt::Key_Right:
    {
        qDebug() <<"droite";
//        add[0]=cameraFront[1]*cameraUp[2]-cameraFront[2]*cameraUp[1];
//        add[1]=cameraFront[2]*cameraUp[0]-cameraFront[0]*cameraUp[2];
//        add[2]=cameraFront[0]*cameraUp[1]-cameraFront[1]*cameraUp[0];
//        norm = sqrt(add[0]*add[0]+add[1]*add[1]+add[2]*add[2]);
//        cameraPos[0] += add[0]/norm;
//        cameraPos[1] += add[1]/norm;
//        cameraPos[2] += add[2]/norm;
        yaw += 5;
        add[0] = cos(yaw*3.14/180)*cos(pitch*3.14/180);
        add[1] = sin(pitch*3.14/180);
        add[2] = sin(yaw*3.14/180)*cos(pitch*3.14/180);
        norm = sqrt(add[0]*add[0]+add[1]*add[1]+add[2]*add[2]);
        cameraFront[0] = add[0]/norm;
        cameraFront[1] = add[1]/norm;
        cameraFront[2] = add[2]/norm;
        break;
    }
    case Qt::Key_Left:
    {
        qDebug() <<"gauche";
//        add[0]=cameraFront[1]*cameraUp[2]-cameraFront[2]*cameraUp[1];
//        add[1]=cameraFront[2]*cameraUp[0]-cameraFront[0]*cameraUp[2];
//        add[2]=cameraFront[0]*cameraUp[1]-cameraFront[1]*cameraUp[0];
//        norm = sqrt(add[0]*add[0]+add[1]*add[1]+add[2]*add[2]);
//        cameraPos[0] -= add[0]/norm;
//        cameraPos[1] -= add[1]/norm;
//        cameraPos[2] -= add[2]/norm;
        yaw -= 5;
        add[0] = cos(yaw*3.14/180)*cos(pitch*3.14/180);
        add[1] = sin(pitch*3.14/180);
        add[2] = sin(yaw*3.14/180)*cos(pitch*3.14/180);
        norm = sqrt(add[0]*add[0]+add[1]*add[1]+add[2]*add[2]);
        cameraFront[0] = add[0]/norm;
        cameraFront[1] = add[1]/norm;
        cameraFront[2] = add[2]/norm;
        break;
    }
    case Qt::Key_Z:
    {
        qDebug() <<"go";
        vaisseauPos[0] += cameraFront[0];
        vaisseauPos[1] += cameraFront[1];
        vaisseauPos[2] += cameraFront[2];
        break;
    }
    case Qt::Key_S:
    {
        qDebug() <<"back";
        vaisseauPos[0] -= cameraFront[0];
        vaisseauPos[1] -= cameraFront[1];
        vaisseauPos[2] -= cameraFront[2];
        break;
    }
    case Qt::Key_Up:
    {
        qDebug() <<"up";
        pitch += 5;
        if(pitch > 89.0f){
            pitch = 89.0f;
        }
        if(pitch < -89.0f){
            pitch = -89.0f;
        }
        add[0] = cos(yaw*3.14/180)*cos(pitch*3.14/180);
        add[1] = sin(pitch*3.14/180);
        add[2] = sin(yaw*3.14/180)*cos(pitch*3.14/180);
        norm = sqrt(add[0]*add[0]+add[1]*add[1]+add[2]*add[2]);
        cameraFront[0] = add[0]/norm;
        cameraFront[1] = add[1]/norm;
        cameraFront[2] = add[2]/norm;
        break;
    }
    case Qt::Key_Down:
    {
        qDebug() <<"down";
        pitch -= 5;
        if(pitch > 89.0f){
            pitch = 89.0f;
        }
        if(pitch < -89.0f){
            pitch = -89.0f;
        }
        add[0] = cos(yaw*3.14/180)*cos(pitch*3.14/180);
        add[1] = sin(pitch*3.14/180);
        add[2] = sin(yaw*3.14/180)*cos(pitch*3.14/180);
        norm = sqrt(add[0]*add[0]+add[1]*add[1]+add[2]*add[2]);
        cameraFront[0] = add[0]/norm;
        cameraFront[1] = add[1]/norm;
        cameraFront[2] = add[2]/norm;
        break;
    }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    update();
}
