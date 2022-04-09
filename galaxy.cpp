#include "galaxy.h"
#include <QImage>

Galaxy::Galaxy()
{
    m_Galaxy=gluNewQuadric();

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

    QImage image_galaxy(":/tex_galaxy2.jpg");
    image_galaxy=image_galaxy.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &tex_galaxy);
    glBindTexture(GL_TEXTURE_2D, tex_galaxy);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image_galaxy.width(), image_galaxy.height(),0, GL_RGBA, GL_UNSIGNED_BYTE, image_galaxy.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    QImage image_logo(":/logoTSE.jpg");
    image_logo=image_logo.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &tex_logo);
    glBindTexture(GL_TEXTURE_2D, tex_logo);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image_logo.width(), image_logo.height(),0, GL_RGBA, GL_UNSIGNED_BYTE, image_logo.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    // création des astéroides
    myAsteroides=new Asteroide[number];
    for(int i=0; i<number; i++){
        myAsteroides[i].Initialise();
        myAsteroides[i].setTexture(tex_asteroide);
    }

    // création de la station orbitale
    myStation=new Station();
    myStation->Initialise();
    myStation->setTexture(tex_logo);

}

Galaxy::~Galaxy()
{
    // Destruction de la quadrique
    if(m_Galaxy)
        gluDeleteQuadric(m_Galaxy);
    for(int i=0;i<number;i++){
        myAsteroides[i].~Asteroide();
    }
    delete[] myAsteroides;
    myStation->~Station();
    delete myStation;

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



    for(int i=0;i<number;i++){
        myAsteroides[i].Display();
        myAsteroides[i].rotation();
    }

    myStation->Display();
    myStation->rotation();
}
