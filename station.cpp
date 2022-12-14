#include "station.h"
#include <cmath>
#include <QDebug>
#include <QImage>

Station::Station()
{
    QImage image_logo(":/logoTSE.jpg");
    image_logo=image_logo.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &tex_logo);
    glBindTexture(GL_TEXTURE_2D, tex_logo);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image_logo.width(), image_logo.height(),0, GL_RGBA, GL_UNSIGNED_BYTE, image_logo.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Station::~Station()
{
    // Destruction de la quadrique
    if(m_Sphere)
        gluDeleteQuadric(m_Sphere);
    if(m_Cylindres)
        gluDeleteQuadric(m_Cylindres);
}

void Station::Initialise(float tempx, float tempy, float tempz)
{
    // création de la quadrique pour la sphère
    m_Sphere=gluNewQuadric();
    // création de la quadrique pour les cylindres
    m_Cylindres=gluNewQuadric();

    x=tempx;
    y=tempy;
    z=tempz;
    outerRadius=5;
}

void Station::rotation()
{
    angle=angle+0.3;
}

void Station::Display() const
{
    // on dessine la sphère centrale
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_logo);

    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glRotatef(angle, 0, 0, -1);

    gluQuadricDrawStyle(m_Sphere, GLU_FILL);
    gluQuadricTexture(m_Sphere, GLU_TRUE);
    gluSphere(m_Sphere, sphereRadius, 20, 20);
    gluQuadricDrawStyle(m_Sphere, GLU_LINE);
    gluSphere(m_Sphere, outerRadius, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // croix de cylindres
    glColor3f(0,0.9,0);
    glPushMatrix();
    glRotatef(angle, 0,1,0);
    glTranslatef(-cylinderLength/2, 0.0f, 0.0f);
    glRotated(90.0, 0., 1., 0.);
    gluCylinder(m_Cylindres, 0.25, 0.25, cylinderLength, 32, 32);
    glPopMatrix();

    glColor3f(0,0,0.9);
    glPushMatrix();
    glRotatef(angle, 0,1,0);
    glTranslatef(0.f, 0.f, -cylinderLength/2);
    gluCylinder(m_Cylindres, 0.25, 0.25, cylinderLength, 32, 32);
    glPopMatrix();

    // le disque supérieur
    glColor3f(0.45,0.45,0.45);
    //    gluQuadricDrawStyle(m_Cylindres, GLU_LINE);
    glPushMatrix();
    glRotatef(angle, 0,1,0);
    glTranslatef(0.f, 0.3f, 0.0f);
    glRotated(90.0, 1.,0 , 0.);
    gluDisk(m_Cylindres, innerRadius, outerRadius, 28, 2);
    glPopMatrix();

    // le disque inférieur
    //    gluQuadricDrawStyle(m_Cylindres, GLU_LINE);
    glPushMatrix();
    glRotatef(angle, 0,1,0);
    glTranslatef(0.f, -0.3f, 0.0f);
    glRotated(90.0, 1.,0 , 0.);
    gluDisk(m_Cylindres, innerRadius, outerRadius, 28, 2);
    glPopMatrix();

    float miniAngle=(360.0*M_PI)/(28.0*180);
    float miniLength;

    // cote interieur
    glColor3f(0.35,0.35,0.35);
    float x0=0;
    float z0=innerRadius;


    float tempX,tempZ;
    glPushMatrix();
    glRotatef(angle, 0,1,0);
    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<29;i++){
        miniLength=sqrt(2*innerRadius*innerRadius*(1-cos((i)*miniAngle)));
        tempX=x0+miniLength*cos((i)*miniAngle/2);
        tempZ=z0-miniLength*sin((i)*miniAngle/2);
        glVertex3f(tempX,-0.3,tempZ);
        glVertex3f(tempX,0.3,tempZ);
    }
    glEnd();

    // cote exterieur
    x0=0;
    z0=outerRadius;
    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<29;i++){
        miniLength=sqrt(2*outerRadius*outerRadius*(1-cos((i)*miniAngle)));
        tempX=x0+miniLength*cos((i)*miniAngle/2);
        tempZ=z0-miniLength*sin((i)*miniAngle/2);
        glVertex3f(tempX,-0.3,tempZ);
        glVertex3f(tempX,0.3,tempZ);
    }
    glEnd();
    glPopMatrix();
    glColor3f(1,1,1);
}
