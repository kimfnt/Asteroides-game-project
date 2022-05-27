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

    m_AnimationTimer.setInterval(50);
    m_AnimationTimer.start();
}

MyGLWidget::~MyGLWidget()
{
    delete myGalaxy;
    delete maStation;
    delete mesAsteroides;
    delete monVaisseau;
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
    maStation->Initialise();

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

    gluLookAt(vaisseauPos[0]-cameraFront[0],vaisseauPos[1]-cameraFront[1],vaisseauPos[2]-cameraFront[2],
            vaisseauPos[0],vaisseauPos[1],vaisseauPos[2],
            cameraUp[0],cameraUp[1],cameraUp[2]);

    // on affiche la galaxy
    myGalaxy->Display();
    myGalaxy->rotation();


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

    glEnable(GL_LIGHTING);
    //Lumière
    GLfloat light_tab[] = {1.0, 1.0, 0.0, 0.0};
    GLfloat lum_ambiante[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lum_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lum_speculaire[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_tab);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lum_ambiante);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lum_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lum_speculaire);
    glEnable(GL_LIGHT0);
    //Placer le vaisseau
    glTranslatef(vaisseauPos[0],vaisseauPos[1],vaisseauPos[2]);
    glRotatef(-yaw-90,cameraUp[0],cameraUp[1],cameraUp[2]);
    glRotatef(pitch+10,1.0,0.0,0.0);
    glScaled(0.05,0.05,0.05);
    glPushMatrix();
    monVaisseau->Display();
    glPopMatrix();
    glDisable(GL_LIGHTING);

    //    qDebug() << vaisseauPos[0] << vaisseauPos[1] << vaisseauPos[2];
    if (state == previous_state)
    {
        if (vitesse <= 4){
            vitesse += 0.5;
        }
    } else {
        vitesse = 0.5;
    }
    previous_state = state;

    // We check collisions
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
        computeMovement(0);
        break;
    }
    case Qt::Key_Q:
    {
        computeMovement(1);
        break;
    }
    case Qt::Key_I:
    {
        computeMovement(2);
        break;
    }
    case Qt::Key_K:
    {
        computeMovement(3);
        break;
    }
    case Qt::Key_Z:
    {
        computeMovement(4);
        break;
    }
    case Qt::Key_S:
    {
        computeMovement(5);
        break;
    }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
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
        state = 1;
        yaw += 0.5*vitesse;
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
        state = 2;
        yaw -= 0.5*vitesse;
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
        state = 3;
        if(vaisseauPos[0]+cameraFront[0]>10 || vaisseauPos[0]+cameraFront[0]<-10 ||
                vaisseauPos[1]+cameraFront[1]>10 || vaisseauPos[1]+cameraFront[1]<-10 ||
                vaisseauPos[2]+cameraFront[2]>13 || vaisseauPos[2]+cameraFront[2]<-25){
            qDebug() <<"limite";
        } else {
            vaisseauPos[0] += cameraFront[0]*vitesse/8;
            vaisseauPos[1] += cameraFront[1]*vitesse/8;
            vaisseauPos[2] += cameraFront[2]*vitesse/8;
            qDebug() <<"go";
        }
        break;
    }
    case 3:
    {
        state = 4;
        if(vaisseauPos[0]-cameraFront[0]>10 || vaisseauPos[0]-cameraFront[0]<-10 ||
                vaisseauPos[1]-cameraFront[1]>10 || vaisseauPos[1]-cameraFront[1]<-10 ||
                vaisseauPos[2]-cameraFront[2]>13 || vaisseauPos[2]-cameraFront[2]<-25){
            qDebug() <<"limite";
        } else {
            vaisseauPos[0] -= cameraFront[0]*vitesse/8;
            vaisseauPos[1] -= cameraFront[1]*vitesse/8;
            vaisseauPos[2] -= cameraFront[2]*vitesse/8;
            qDebug() <<"back";
        }
        break;
    }
    case 4:
    {
        qDebug() <<"up";
        state = 5;
        pitch += 0.5*vitesse;
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
        state = 6;
        pitch -= 0.5*vitesse;
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
    float radiusOne=0.25;
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

