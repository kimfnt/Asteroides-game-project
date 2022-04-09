#include "asteroide.h"
#include <QDebug>
#include <QImage>

Asteroide::Asteroide()
{
}

Asteroide::~Asteroide()
{
    // Destruction de la quadrique
    if(m_Asteroide)
        gluDeleteQuadric(m_Asteroide);
}

void Asteroide::Initialise()
{
    // création de la quadrique
    m_Asteroide=gluNewQuadric();

    // choix de la taille de l'asteroide à partir des tailles disponibles
    size=sizeAvailable[rand()%5];

    // détermination de la localisation de l'asteroide
    pos[0]=low + ((float)rand()) * (float)(high - low) / RAND_MAX;
    pos[1]=low + ((float)rand()) * (float)(high - low) / RAND_MAX;
    pos[2]=low + ((float)rand()) * (float)(high - low) / RAND_MAX;

    // détermination d'un angle de rotation entre -45 et 45
    angle=-45. + ((float)rand()) * (float)(45. - (-45.)) / RAND_MAX;

    // determination d'une vitesse de rotation entre -2 et 2
    while(true){
        vitesse=-2.+((float)rand()) * (float)(2.0-(-2.)) / RAND_MAX;
        if(vitesse<=-0.5 || vitesse >=0.5)
            break;
    }

}

void Asteroide::setTexture(GLuint tex)
{
    tex_asteroide=tex;
}

void Asteroide::rotation()
{
    rot=(rot+vitesse);
}

void Asteroide::Display() const
{
    // on active la texture 2D
    glEnable(GL_TEXTURE_2D);

    // on définit la texture courante
    glBindTexture(GL_TEXTURE_2D, tex_asteroide);

    // on définit l'affichage en mode plein
    gluQuadricDrawStyle(m_Asteroide, GLU_FILL);

    glPushMatrix();
    glRotatef(90, 1,0,0);
    // on active la texture sur l'asteroide
    gluQuadricTexture(m_Asteroide, GLU_TRUE);

    glTranslatef(pos[0], pos[1], pos[2]);

    // Rotation de l'asteroide
    glRotatef(rot, 0, 0, 1);
    glRotatef(angle, 0,1,0);
    // on dessine l'asteroide avec la taille aléatoire
    gluSphere(m_Asteroide, size, 20, 20);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

