#ifndef GALAXY_H
#define GALAXY_H
#include "asteroide.h"
#include "station.h"
#include <list>
using namespace std;

class Galaxy
{
public:
    // constructeur
    Galaxy();

    // destructeur
    ~Galaxy();

    // fonction d'affichage
    void Display() const;

    // fonction pour la rotation
    void rotation(){rot += 0.5;}

private:
    GLUquadric * m_Galaxy;

    // textures pour les éléments
    GLuint tex_galaxy;
    GLuint tex_neptune;
    GLuint tex_soleil;

    // rotation
    float rot = 0;
};

#endif // GALAXY_H
