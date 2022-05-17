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

    void Display(uint64_t iTimeElapsed) const;
    GLUquadric* quad;
};

#endif // VAISSEAU_H
