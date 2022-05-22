#include "galaxy.h"
#include <QImage>
#include <QDebug>

using namespace std;
Galaxy::Galaxy()
{
    m_Galaxy=gluNewQuadric();

    QImage image_galaxy(":/tex_galaxy2.jpg");
    image_galaxy=image_galaxy.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &tex_galaxy);
    glBindTexture(GL_TEXTURE_2D, tex_galaxy);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image_galaxy.width(), image_galaxy.height(),0, GL_RGBA, GL_UNSIGNED_BYTE, image_galaxy.bits());
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
    gluSphere(m_Galaxy, 200, 20, 20);

    glDisable(GL_TEXTURE_2D);
}
