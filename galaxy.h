#ifndef GALAXY_H
#define GALAXY_H
#include "asteroide.h"
#include "station.h"
#include <list>
using namespace std;

class Galaxy
{
public:
    Galaxy();
    ~Galaxy();

    // fonction d'affichage
    void Display() const;
    void rotation(){rot += 0.5;}

private:
    GLUquadric * m_Galaxy { nullptr };
    GLuint tex_galaxy;
    GLuint tex_neptune;
    GLuint tex_soleil;

    float rot = 0;
};

#endif // GALAXY_H
