#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>

// Classe dédiée à la gestion des astéroides
class Asteroide
{
public:
    // Constructeur avec parametres
    Asteroide();

    // Destructeur
    ~Asteroide();

    // Initialisation de l'asteroide
    void Initialise();

    // incrémentation de la rotation
    void rotation();

    // Methode d'affichage
    void Display() const;

    // getters
    float getX(){return x;};
    float getY(){return y;};
    float getZ(){return z;};
    float getRadius(){return size;};

private:
    float sizeAvailable[8]={0.5, 0.75, 1, 1.25, 1.5, 1.75, 2, 2.5};
    float size;
    // Coordonnées de l'emplacement de l'astéroide
    float x=0;
    float y=0;
    float z=0;

    // valeurs pour le spawn
    float low_x=-5.0;
    float high_x=5.0;
    float low_y=-5.0;
    float high_y=5.0;
    float low_z=-20.0;
    float high_z=10.0;

    // rotation
    float rot=0;
    float angle=0;
    float vitesse=0;

    GLUquadric * m_Asteroide { nullptr };
    GLuint tex_asteroide;
};

#endif // ASTEROIDE_H
