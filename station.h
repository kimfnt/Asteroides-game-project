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

    void Initialise(float, float, float);

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
    float x;
    float y;
    float z;
    float innerRadius=4;
    float outerRadius=5;

    float sphereRadius = 2;
    float cylinderLength = 8;
    float angle=0;
    GLUquadric * m_Sphere = nullptr;
    GLUquadric * m_Cylindres { nullptr };
    GLuint tex_logo;
};

#endif // STATION_H
