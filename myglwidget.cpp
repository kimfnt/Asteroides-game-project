#include "myglwidget.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include <QGuiApplication>
#include "qscreen.h"


MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent)
{
    // Reglage de la taille/position
    //setFixedSize(810, 780);

    QRect  screenGeometry= QGuiApplication::primaryScreen()->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    setFixedSize(width/2, height-100);

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

    // création de la galaxie
    myGalaxy=new Galaxy();

    // création de la station spatiale
    maStation=new Station();
    maStation->Initialise(10,0,-10);

    // création des astéroides
    mesAsteroides = new Asteroide[nombre];
    for(int i = 0; i < nombre; i++){
        Asteroide *toCreate= new Asteroide();
        do {
            toCreate->Initialise();
        } while(overlap(toCreate, i));
        mesAsteroides[i]=*toCreate;
    }

    // création du vaisseau spatial
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
    gluLookAt(vaisseauPos[0]-cameraFront[0],vaisseauPos[1]-cameraFront[1],vaisseauPos[2]-cameraFront[2],
            vaisseauPos[0],vaisseauPos[1],vaisseauPos[2],
            cameraUp[0],cameraUp[1],cameraUp[2]);

    //glDisable(GL_LIGHTING); // on désactive le lighting pour dessiner la route

    //glEnable(GL_LIGHTING); // on réactive le lighting par la suite


    // translation des éléments suivants (voiture, roues, phares) sur l'axe x
    //glTranslatef(placement, 0.f, 0.f);

    // on affiche la galaxy
    myGalaxy->Display();

    // on affiche la station spatiale
    float x=maStation->getX();
    float y=maStation->getY();
    float z=maStation->getZ();
    glPushMatrix();
    glTranslatef(x,y,z);
    maStation->Display();
    glPopMatrix();
    maStation->rotation();

    // on affiche les asteroides
    for(int i=0;i<nombre;i++){
        float x=mesAsteroides[i].getX();
        float y=mesAsteroides[i].getY();
        float z=mesAsteroides[i].getZ();

        glPushMatrix();
        glTranslatef(x, y, z);
        mesAsteroides[i].Display();
        glPopMatrix();
        mesAsteroides[i].rotation();
    }

    //Placer le vaisseau
    glTranslatef(vaisseauPos[0],vaisseauPos[1],vaisseauPos[2]);
    glRotatef(-yaw-90,0.0,1.0,0.0);
    glRotatef(pitch+10,1.0,0.0,0.0);
    glScaled(0.05,0.05,0.05);
    glPushMatrix();
    monVaisseau->Display(0);
    glPopMatrix();

    if(end==false)
        checkCollision();
}

void MyGLWidget::asteroidsChange(int nb)
{
    nombre=nb;
}

// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key()){
    // Cas par defaut
    default:
    {
        // Ignorer l'evenement
        event->ignore();
        return;
    }
    case Qt::Key_D:
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
    case Qt::Key_Q:
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
    case Qt::Key_I:
    {
        qDebug() <<"go";
        vaisseauPos[0] += cameraFront[0];
        vaisseauPos[1] += cameraFront[1];
        vaisseauPos[2] += cameraFront[2];
        break;
    }
    case Qt::Key_K:
    {
        qDebug() <<"back";
        vaisseauPos[0] -= cameraFront[0];
        vaisseauPos[1] -= cameraFront[1];
        vaisseauPos[2] -= cameraFront[2];
        break;
    }
    case Qt::Key_Z:
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
    case Qt::Key_S:
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


/**
 * function to compute the movement of the space ship in the scene
 * @brief MyGLWidget::computeMovement
 * @param move an integer
 */
void MyGLWidget::computeMovement(int move)
{
    switch(move)
    {
    default:
    {
    }
    case 0:
    {
        qDebug() <<"droite";
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
    case 1:
    {
        qDebug() <<"gauche";
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
    case 2:
    {
        qDebug() <<"go";
        vaisseauPos[0] += cameraFront[0];
        vaisseauPos[1] += cameraFront[1];
        vaisseauPos[2] += cameraFront[2];
        break;
    }
    case 3:
    {
        qDebug() <<"back";
        vaisseauPos[0] -= cameraFront[0];
        vaisseauPos[1] -= cameraFront[1];
        vaisseauPos[2] -= cameraFront[2];
        break;
    }
    case 4:
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
    case 5:
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
    update();
}


/**
 * function that checks if the new asteroid overlaps with the
 * space station or an asteroid
 * @brief MyGLWidget::overlap
 * @param toCreate a pointer to the generated asteroid
 * @param nb the number of asteroids actually in the array
 * @return bool that indicates if there is an overlapping
 */
bool MyGLWidget::overlap(Asteroide* toCreate, int nb){

    // on vérifie que l'asteroide ne chevauche pas la station spatiale
    float distX=toCreate->getX()-this->maStation->getX();
    float distY=toCreate->getY()-this->maStation->getY();
    float distZ=toCreate->getZ()-this->maStation->getZ();

    float dist = sqrt(distX*distX+distY*distY+distZ*distZ);
    float radiusOne=toCreate->getRadius();
    float radiusTwo=this->maStation->getRadius();

    if(dist <= (radiusOne+radiusTwo)){
        return true;
    }

    // on vérifie que l'asteroide ne chevauche pas une asteroide déjà crée
    for(int i=0; i<nb;i++){
        distX=toCreate->getX()-this->mesAsteroides[i].getX();
        distY=toCreate->getY()-this->mesAsteroides[i].getY();
        distZ=toCreate->getZ()-this->mesAsteroides[i].getZ();

        dist = sqrt(distX*distX+distY*distY+distZ*distZ);
        radiusTwo=this->mesAsteroides[i].getRadius();
        if(dist <= (radiusOne+radiusTwo)){
            return true;
        }
    }
    return false;
}


/**
 * @brief MyGLWidget::checkCollision
 * function that checks if the space ship has collided with an element
 */
void MyGLWidget::checkCollision()
{
    // on regarde si le vaisseau est arrivé à la station
    float distX=vaisseauPos[0]-this->maStation->getX();
    float distY=vaisseauPos[1]-this->maStation->getY();
    float distZ=vaisseauPos[2]-this->maStation->getZ();

    float dist = sqrt(distX*distX+distY*distY+distZ*distZ);
    float radiusOne=0.275;
    float radiusTwo=this->maStation->getRadius();

    if(dist <= (radiusOne+radiusTwo)){
        end=true;
        emit endOfGame(true);
    }

    // on regarde si le vaisseau est en collision avec une astéroide
    for(int i=0; i<nombre;i++){
        distX=vaisseauPos[0]-this->mesAsteroides[i].getX();
        distY=vaisseauPos[1]-this->mesAsteroides[i].getY();
        distZ=vaisseauPos[2]-this->mesAsteroides[i].getZ();

        dist = sqrt(distX*distX+distY*distY+distZ*distZ);
        radiusTwo=this->mesAsteroides[i].getRadius();
        if(dist <= (radiusOne+radiusTwo)){
            end=true;
            emit endOfGame(false);
        }
    }
}

