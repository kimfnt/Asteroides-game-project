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

private:
    GLUquadric * m_Galaxy { nullptr };
    GLuint tex_galaxy;
};

#endif // GALAXY_H
