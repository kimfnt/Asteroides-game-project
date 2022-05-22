#include "asteroide.h"
#include <QDebug>
#include <QImage>

Asteroide::Asteroide()
{
    // Conversion de l'image en un format attendu par les fonctions OpenGL
    QImage image(":/tex2.jpg");
    image=image.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &tex_asteroide);
    glBindTexture(GL_TEXTURE_2D, tex_asteroide);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image.width(), image.height(),0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

Asteroide::~Asteroide()
{
    // Destruction de la quadrique
    if(m_Asteroide)
        gluDeleteQuadric(m_Asteroide);
}

/**
 * function that initialises the size, the position of the asteroid,
 * the angle of rotation and speed
 * @brief Asteroide::Initialise
 */
void Asteroide::Initialise()
{
    // création de la quadrique
    m_Asteroide=gluNewQuadric();

    // choix de la taille de l'asteroide à partir des tailles disponibles
    size=sizeAvailable[rand()%5];

    // détermination de la localisation de l'asteroide
    x=low + ((float)rand()) * (float)(high - low) / RAND_MAX;
    y=low + ((float)rand()) * (float)(high - low) / RAND_MAX;
    z=low + ((float)rand()) * (float)(high - low) / RAND_MAX;

    // détermination d'un angle de rotation entre -45 et 45
    angle=-45. + ((float)rand()) * (float)(45. - (-45.)) / RAND_MAX;

    // determination d'une vitesse de rotation entre -2 et 2
    while(true){
        vitesse=-2.+((float)rand()) * (float)(2.0-(-2.)) / RAND_MAX;
        if(vitesse<=-0.5 || vitesse >=0.5)
            break;
    }

}

/**
 * function that increments the rotation
 * @brief Asteroide::rotation
 */
void Asteroide::rotation()
{
    rot=(rot+vitesse);
}

/**
 * function that displays the asteroid
 * @brief Asteroide::Display
 */
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

    // Rotation de l'asteroide
    glRotatef(rot, 0, 0, 1);
    glRotatef(angle, 0,1,0);
    // on dessine l'asteroide avec la taille aléatoire
    gluSphere(m_Asteroide, size, 20, 20);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

