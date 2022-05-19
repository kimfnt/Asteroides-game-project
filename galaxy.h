#ifndef GALAXY_H
#define GALAXY_H
#include "asteroide.h"
#include "station.h"

class Galaxy
{
public:
    Galaxy(int nb);
    ~Galaxy();
    void Display() const;

private:
    int number;
    Asteroide* myAsteroides={nullptr};
    Station* myStation=nullptr;

    GLUquadric * m_Galaxy { nullptr };
    GLuint tex_asteroide;
    GLuint tex_galaxy;
    GLuint tex_logo;
};

#endif // GALAXY_H
