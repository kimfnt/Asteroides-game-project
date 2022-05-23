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

    //def des variables pour effet chrome
    GLfloat chrome_ambiante[] = {0.25, 0.25, 0.25, 1.0};
    GLfloat chrome_diffuse[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat chrome_speculaire[] = {0.774597, 0.774597, 0.774597, 1.0};
    GLfloat chrome_emission[] = {0.0, 0.0, 0.0, 1.0};
    float shininess = 0.6f;


    //def des variables pour effet plastic noir
    GLfloat plastic_noir_ambiante[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat plastic_noir_diffuse[] = {0.01, 0.01, 0.01, 0.0};
    GLfloat plastic_noir_speculaire[] = {0.05, 0.05, 0.05, 0.0};
    GLfloat plastic_noir_emission[] = {0.0, 0.0, 0.0, 0.0};
    float shininess3 = 0.25f;


    glMaterialfv(GL_FRONT, GL_AMBIENT, chrome_ambiante);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chrome_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, chrome_speculaire);
    glMaterialfv(GL_FRONT, GL_EMISSION, chrome_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    //corps
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluCylinder(quad, 1.2, 1.2, 6, 10, 10);
    // base, haut, hauteur

    //pointe
    glPushMatrix();
    glTranslatef(0.f,0.f,-5.f);
    gluCylinder(quad, 0, 1.2, 5,10, 10);
    glPopMatrix();

    //base
    glPushMatrix();
    glTranslatef(0.f,0.f,6.f);
    gluDisk(quad, 0, 1.2, 10, 10);

    glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_noir_ambiante);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_noir_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_noir_speculaire);
    glMaterialfv(GL_FRONT, GL_EMISSION, plastic_noir_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess3);

    glTranslatef(0.f,0.f,0.01f);
    gluDisk(quad,1.15,1.2,10,10);
    glPopMatrix();



    //pot
    glPushMatrix();
    glTranslatef(0.6f,0.6f,5.f);
    gluCylinder(quad, 0.6, 0.65, 1.4, 10, 10);

    gluDisk(quad,0,0.6,10,10);
    glTranslatef(0.f,0.f,1.4f);
    gluDisk(quad,0,0.65,10,10);
    glTranslatef(0.f,0.f,-1.4f);


    glTranslatef(-1.2f,0.f,0.f);
    gluCylinder(quad, 0.6, 0.65, 1.4, 10, 10);
    gluDisk(quad,0,0.6,10,10);
    glTranslatef(0.f,0.f,1.4f);
    gluDisk(quad,0,0.65,10,10);
    glTranslatef(0.f,0.f,-1.4f);

    glTranslatef(0.f,-1.2f,0.f);
    gluCylinder(quad, 0.6, 0.65, 1.4, 10, 10);
    gluDisk(quad,0,0.6,10,10);
    glTranslatef(0.f,0.f,1.4f);
    gluDisk(quad,0,0.65,10,10);
    glTranslatef(0.f,0.f,-1.4f);

    glTranslatef(1.2f,0.f,0.f);
    gluCylinder(quad, 0.6, 0.65, 1.4, 10, 10);
    gluDisk(quad,0,0.6,10,10);
    glTranslatef(0.f,0.f,1.4f);
    gluDisk(quad,0,0.65,10,10);
    glTranslatef(0.f,0.f,-1.4f);
    glPopMatrix();



    //ailes
    glMaterialfv(GL_FRONT, GL_AMBIENT, chrome_ambiante);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chrome_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, chrome_speculaire);
    glMaterialfv(GL_FRONT, GL_EMISSION, chrome_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    //aile gauche
    glNormal3f(-0.84/(sqrt(0.84*0.84+9.6*9.6+0.48*0.48)), 9.6/(sqrt(0.84*0.84+9.6*9.6+0.48*0.48)), -0.48/(sqrt(0.84*0.84+9.6*9.6+0.48*0.48)));
    glVertex3f(-1.2f, 0.f, 1.f);
    glVertex3f(-1.2f, 0.2f, 5.f);
    glVertex3f(-3.6f, 0.f, 5.2f);

    glNormal3f(-0.84/(sqrt(0.84*0.84+9.6*9.6+0.48*0.48)),-9.6/(sqrt(0.84*0.84+9.6*9.6+0.48*0.48)),-0.48/(sqrt(0.84*0.84+9.6*9.6+0.48*0.48)));
    glVertex3f(-1.2f, 0.f, 1.f);
    glVertex3f(-1.2f, -0.2f, 5.f);
    glVertex3f(-3.6f, 0.f, 5.2f);

    glNormal3f(0.08/(sqrt(0.08*0.08+0.96*0.96)), 0.f, 0.96/(sqrt(0.08*0.08+0.96*0.96)));
    glVertex3f(-1.2f, 0.2f, 5.f);
    glVertex3f(-1.2f, -0.2f, 5.f);
    glVertex3f(-3.6f, 0.f, 5.2f);

    //aile droite
    glNormal3f(0.84/sqrt(0.84*0.84+9.6*9.6+0.48*0.48),9.6/sqrt(0.84*0.84+9.6*9.6+0.48*0.48),-0.48/sqrt(0.84*0.84+9.6*9.6+0.48*0.48));
    glVertex3f(1.2f, 0.f, 1.f);
    glVertex3f(1.2f, 0.2f, 5.f);
    glVertex3f(3.6f, 0.f, 5.2f);

    glNormal3f(0.84/sqrt(0.84*0.84+9.6*9.6+0.48*0.48),-9.6/sqrt(0.84*0.84+9.6*9.6+0.48*0.48),-0.48/sqrt(0.84*0.84+9.6*9.6+0.48*0.48));
    glVertex3f(1.2f, 0.f, 1.f);
    glVertex3f(1.2f, -0.2f, 5.f);
    glVertex3f(3.6f, 0.f, 5.2f);

    glNormal3f(-0.08/sqrt(0.08*0.08+0.48*0.48),0,0.96/sqrt(0.08*0.08+0.96*0.96));
    glVertex3f(1.2f, 0.2f, 5.f);
    glVertex3f(1.2f, -0.2f, 5.f);
    glVertex3f(3.6f, 0.f, 5.2f);
    glEnd();

    glPopMatrix();

}
