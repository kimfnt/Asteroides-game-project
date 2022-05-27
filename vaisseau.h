#ifndef VAISSEAU_H
#define VAISSEAU_H
#include <qopengl.h>
#include <GL/glu.h>
#include <QDebug>

class Vaisseau
{
public:
    Vaisseau();
    ~Vaisseau();

    // fonction d'affichage
    void Display() const;

private:
    GLUquadric* m_Vaisseau;
};

#endif // VAISSEAU_H
