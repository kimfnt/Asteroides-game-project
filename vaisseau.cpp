#include "vaisseau.h"

Vaisseau::Vaisseau()
{
    quad = gluNewQuadric();
}

Vaisseau::~Vaisseau()
{
    gluDeleteQuadric(quad);
}

void Vaisseau::Display(uint64_t iTimeElapsed) const{

    //corps
    gluQuadricDrawStyle(quad, GLU_FILL);
    glColor3f(0.6f, 0.6f, 0.6f);
    gluCylinder(quad, 1.2, 1.2, 6, 10, 10);
    gluQuadricDrawStyle(quad, GLU_LINE);
    gluSphere(quad, 6.2, 20,20);
    // base, haut, hauteur

    //base
    glPushMatrix();
    glTranslatef(0.f,0.f,6.f);
    glColor3f(0.5f, 0.5f, 0.5f);
    gluDisk(quad, 0, 1.2, 10, 10);
    glPopMatrix();

    //pointe
    glPushMatrix();
    glTranslatef(0.f,0.f,-5.f);
    glColor3f(0.7f, 0.7f, 0.7f);
    gluCylinder(quad, 0, 1.2, 5,10, 10);
    glPopMatrix();

    //pot
    glPushMatrix();
    glTranslatef(0.6f,0.6f,5.f);
    glColor3f(0.1f, 0.1f, 0.1f);
    gluCylinder(quad, 0.6, 0.65, 1.4, 10, 10);

    glTranslatef(-1.2f,0.f,0.f);
    gluCylinder(quad, 0.6, 0.65, 1.4, 10, 10);

    glTranslatef(0.f,-1.2f,0.f);
    gluCylinder(quad, 0.6, 0.65, 1.4, 10, 10);

    glTranslatef(1.2f,0.f,0.f);
    gluCylinder(quad, 0.6, 0.65, 1.4, 10, 10);
    glPopMatrix();

    //ailes
    glPushMatrix();
    glColor3f(1.f,1.f,1.f);
    glBegin(GL_TRIANGLES);
    //aile gauche
    glVertex3f(-1.2f, 0.f, 1.f);
    glVertex3f(-1.2f, 0.2f, 5.f);
    glVertex3f(-3.6f, 0.f, 5.2f);
    //glColor3f(0.f,0.f,0.f);
    glVertex3f(-1.2f, 0.f, 1.f);
    glVertex3f(-1.2f, -0.2f, 5.f);
    glVertex3f(-3.6f, 0.f, 5.2f);

    glVertex3f(-1.2f, 0.2f, 5.f);
    glVertex3f(-1.2f, -0.2f, 5.f);
    glVertex3f(-3.6f, 0.f, 5.2f);

    //aile droite
    glColor3f(1.f,1.f,1.f);
    glVertex3f(1.2f, 0.f, 1.f);
    glVertex3f(1.2f, 0.2f, 5.f);
    glVertex3f(3.6f, 0.f, 5.2f);
    //glColor3f(0.f,0.f,0.f);
    glVertex3f(1.2f, 0.f, 1.f);
    glVertex3f(1.2f, -0.2f, 5.f);
    glVertex3f(3.6f, 0.f, 5.2f);

    glVertex3f(1.2f, 0.2f, 5.f);
    glVertex3f(1.2f, -0.2f, 5.f);
    glVertex3f(3.6f, 0.f, 5.2f);
    glEnd();
    glPopMatrix();

}
