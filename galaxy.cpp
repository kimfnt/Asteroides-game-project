#include "galaxy.h"
#include <QImage>
#include <QDebug>

using namespace std;
Galaxy::Galaxy()
{
    m_Galaxy=gluNewQuadric();

    QImage image_galaxy(":/tex_galaxy.jpg");
    image_galaxy=image_galaxy.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &tex_galaxy);
    glBindTexture(GL_TEXTURE_2D, tex_galaxy);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image_galaxy.width(), image_galaxy.height(),0, GL_RGBA, GL_UNSIGNED_BYTE, image_galaxy.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    QImage image_neptune(":/neptune.jpg");
    image_neptune=image_neptune.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &tex_neptune);
    glBindTexture(GL_TEXTURE_2D, tex_neptune);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image_neptune.width(), image_neptune.height(),0, GL_RGBA, GL_UNSIGNED_BYTE, image_neptune.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    QImage image_soleil(":/soleil.jpg");
    image_soleil=image_soleil.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &tex_soleil);
    glBindTexture(GL_TEXTURE_2D, tex_soleil);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image_soleil.width(), image_soleil.height(),0, GL_RGBA, GL_UNSIGNED_BYTE, image_soleil.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Galaxy::~Galaxy()
{
    // Destruction de la quadrique
    if(m_Galaxy)
        gluDeleteQuadric(m_Galaxy);
}

void Galaxy::Display() const
{
    // on active la texture 2D
    glEnable(GL_TEXTURE_2D);

    // on définit la texture courante
    glBindTexture(GL_TEXTURE_2D, tex_galaxy);

    // on définit l'affichage en mode plein
    gluQuadricDrawStyle(m_Galaxy, GLU_FILL);

    // on active la texture sur la galaxie
    gluQuadricTexture(m_Galaxy, GLU_TRUE);

    // on dessine la galaxie
    glPushMatrix();
    glRotatef(90.f, 1.f,0.f,0.f);
    gluSphere(m_Galaxy, 200, 20, 20);
    glPopMatrix();

    //Meme chose pour neptune

    // on définit la texture courante
    glBindTexture(GL_TEXTURE_2D, tex_neptune);

    // on définit l'affichage en mode plein
    gluQuadricDrawStyle(m_Galaxy, GLU_FILL);

    // on active la texture sur neptune
    gluQuadricTexture(m_Galaxy, GLU_TRUE);

    // on se déplace
    glPushMatrix();
    glTranslatef(80.f,-10.f,-80.f);
    glRotatef(80.f, 1.f,0.f,0.f);
    glRotatef(rot, 0.f,0.f,1.f);

    // on dessine neptune
    gluSphere(m_Galaxy, 15, 20, 20);

    glPopMatrix();

    //Meme chose pour le soleil

    // on définit la texture courante
    glBindTexture(GL_TEXTURE_2D, tex_soleil);

    // on définit l'affichage en mode plein
    gluQuadricDrawStyle(m_Galaxy, GLU_FILL);

    // on active la texture sur le soleil
    gluQuadricTexture(m_Galaxy, GLU_TRUE);

    // on se déplace
    glPushMatrix();
    glTranslatef(100.f,100.f,0.f);
    glRotatef(90.f, 1.f,0.f,0.f);

    // on dessine neptune
    gluSphere(m_Galaxy, 10, 20, 20);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
