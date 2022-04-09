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
    void Initialise();
    void rotation();
    // Mise en place de la texture
    void setTexture(GLuint tex);
    void Display() const;

private:
    float pos[3]={0,0,-5};
    float sphereRadius = 2;
    float cylinderLength = 8;
    float angle=0;
    GLUquadric * m_Sphere = nullptr;
    GLUquadric * m_Cylindres { nullptr };
    GLuint tex_logo;
};

#endif // STATION_H
