#ifndef STATION_H
#define STATION_H

#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Station
{
public:
    Station();
    ~Station();

    // fonction d'initialisation
    void Initialise();

    // fonction permettant la rotation de la station
    void rotation();

    // fonction d'affichage
    void Display() const;

    // getters
    float getX(){return x;};
    float getY(){return y;};
    float getZ(){return z;};
    float getRadius(){return outerRadius;};

private:
    // coordonnees de la station
    float x;
    float y;
    float z;
    float outerRadius=5;

    // valeurs pour le spawn
    float low_x=-3.0;
    float high_x=3.0;
    float low_y=-3.0;
    float high_y=3.0;

    float rot=0;
    GLUquadric * m_Station;
    GLuint tex_logo;

    //def des variables pour effet chrome
    GLfloat a_l[4] = {0, 0, 0, 1.0};
    GLfloat d_l[4] = {0, 0, 0, 1.0};
    GLfloat s_l[4] = {0, 0, 0, 1.0};

    float sh_l = 0.4f;

    //def des variables pour effet chrome
    GLfloat a_p[4] = {0, 0, 0, 1.0};
    GLfloat d_p[4] = {0.01, 0.01, 0.01, 1.0};
    GLfloat s_p[4] = {0, 0, 0, 1.0};
    GLfloat e_p[4] = {0, 0, 0, 1.0};
    float sh_p = 0.f;
};

#endif // STATION_H
