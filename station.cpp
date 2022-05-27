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
    if(m_Station)
        gluDeleteQuadric(m_Station);
}

void Station::Initialise()
{
    // création de la quadrique pour la station
    m_Station=gluNewQuadric();

    x=low_x + ((float)rand()) * (float)(high_x - low_x) / RAND_MAX;
    y=low_y + ((float)rand()) * (float)(high_y - low_y) / RAND_MAX;
    z=-20;

    //Lampe clignotante
    GLfloat lum_ambiante_cg[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat lum_diffuse_cg[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat lum_speculaire_cg[] = {0.0, 0.0, 0.0, 1.0};

    glLightfv(GL_LIGHT1, GL_AMBIENT, lum_ambiante_cg);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lum_diffuse_cg);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lum_speculaire_cg);
}

void Station::rotation()
{
    rot=rot+0.3;
}

void Station::Display() const
{
    // on dessine la sphère centrale
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_logo);

    glPushMatrix();
    // TODO
    glRotatef(90, 1, 0, 0);
    glRotatef(rot, 0, 0, -1);

    gluQuadricDrawStyle(m_Station, GLU_FILL);
    gluQuadricTexture(m_Station, GLU_TRUE);
    gluSphere(m_Station, 2, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //def des variables pour effet chrome
    GLfloat ambiante[] = {0.09225, 0.09225, 0.09225, 1.0};
    GLfloat diffuse[] = {0.20724, 0.20724, 0.20724, 1.0};
    GLfloat speculaire[] = {0.408273, 0.408273, 0.408273, 1.0};
    GLfloat emission[] = {0.0, 0.0, 0.0, 1.0};
    float shininess = 0.4f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiante);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, speculaire);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    //Antenne
    glPushMatrix();

    glTranslatef(0,3,0);
    glPushMatrix();
    glRotatef(90,1,0,0);
    gluCylinder(m_Station,0.05,0.05,3,10,10);
    glPopMatrix();


    glRotatef(3*rot,0,1,0);
    glRotatef(45+15*cos(rot/3),-1,0,0);

    //partie interieur, effet "chrome"

    if(int(10*rot)%100<50){
        glEnable(GL_LIGHT1);
    } else {
        glDisable(GL_LIGHT1);
    }

    glBegin(GL_POLYGON);
    glNormal3f(0,1,0);
    glVertex3f(0.125,0,-0.25);
    glVertex3f(0.25,0,0);
    glVertex3f(0.125,0,0.25);
    glVertex3f(-0.125,0,0.25);
    glVertex3f(-0.25,0,0);
    glVertex3f(-0.125,0,-0.25);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0,0.058/sqrt(0.058*0.058+0.063*0.063),0.063/sqrt(0.058*0.058+0.063*0.063));
    glVertex3f(-0.125,0,-0.25);
    glVertex3f(0.125,0,-0.25);
    glVertex3f(0.25,0.25,-0.48);
    glVertex3f(-0.25,0.25,-0.48);

    glNormal3f(-0.063/sqrt(0.031*0.031+0.063*0.063+0.063*0.063),0.063/sqrt(0.031*0.031+0.063*0.063+0.063*0.063),0.031/sqrt(0.031*0.031+0.063*0.063+0.063*0.063));
    glVertex3f(0.125,0,-0.25);
    glVertex3f(0.25,0,0);
    glVertex3f(0.5,0.25,0);
    glVertex3f(0.25,0.25,-0.48);

    glNormal3f(-0.063/sqrt(0.06*0.06+0.063*0.063+0.031*0.031),0.06/sqrt(0.06*0.06+0.063*0.063+0.031*0.031),-0.031/sqrt(0.06*0.06+0.063*0.063+0.031*0.031));
    glVertex3f(0.25,0,0);
    glVertex3f(0.125,0,0.25);
    glVertex3f(0.25,0.25,0.48);
    glVertex3f(0.5,0.25,0);

    glNormal3f(0,0.058/sqrt(0.058*0.058+0.063*0.063),-0.063/sqrt(0.058*0.058+0.063*0.063));
    glVertex3f(0.125,0,0.25);
    glVertex3f(-0.125,0,0.25);
    glVertex3f(-0.25,0.25,0.48);
    glVertex3f(0.25,0.25,0.48);

    glNormal3f(0.063/sqrt(0.063*0.063+0.063*0.063+0.031*0.031),-0.063/sqrt(0.063*0.063+0.063*0.063+0.031*0.031),-0.031/sqrt(0.063*0.063+0.063*0.063+0.031*0.031));
    glVertex3f(-0.125,0,0.25);
    glVertex3f(-0.25,0,0);
    glVertex3f(-0.5,0.25,0);
    glVertex3f(-0.25,0.25,0.48);

    glNormal3f(0.063/sqrt(0.063*0.063+0.06*0.06+0.031*0.031),0.06/sqrt(0.063*0.063+0.06*0.06+0.031*0.031),0.031/sqrt(0.063*0.063+0.06*0.06+0.031*0.031));
    glVertex3f(-0.25,0,0);
    glVertex3f(-0.125,0,-0.25);
    glVertex3f(-0.25,0.25,-0.48);
    glVertex3f(-0.5,0.25,0);
    glEnd();

    glPushMatrix();
    glRotatef(90,-1,0,0);
    gluCylinder(m_Station,0.02,0,0.25,10,10);

    glTranslatef(0,0,0.25);
    GLfloat light_tab_cg[] = {0, -0.1, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_tab_cg);

    if(int(10*rot)%100<50){
        GLfloat e_l[4] = {1, 0, 0, 1.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, a_l);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, d_l);
        glMaterialfv(GL_FRONT, GL_SPECULAR, s_l);
        glMaterialfv(GL_FRONT, GL_EMISSION, e_l);
        glMaterialf(GL_FRONT, GL_SHININESS, sh_l);
    } else {
        GLfloat e_l[4] = {0,0,0,1};
        glMaterialfv(GL_FRONT, GL_AMBIENT, a_l);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, d_l);
        glMaterialfv(GL_FRONT, GL_SPECULAR, s_l);
        glMaterialfv(GL_FRONT, GL_EMISSION, e_l);
        glMaterialf(GL_FRONT, GL_SHININESS, sh_l);
    }
    gluSphere(m_Station,0.015,10,10);

    glDisable(GL_LIGHT1);

    glPopMatrix();



    glMaterialfv(GL_FRONT, GL_AMBIENT, a_p);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d_p);
    glMaterialfv(GL_FRONT, GL_SPECULAR, s_p);
    glMaterialfv(GL_FRONT, GL_EMISSION, e_p);
    glMaterialf(GL_FRONT, GL_SHININESS, sh_p);

    //partie exterieur, plastique noir mate
    glBegin(GL_POLYGON);
    glNormal3f(0,1,0);
    glVertex3f(0.125,-0.1,-0.25);
    glVertex3f(0.25,-0.1,0);
    glVertex3f(0.125,-0.1,0.25);
    glVertex3f(-0.125,-0.1,0.25);
    glVertex3f(-0.25,-0.1,0);
    glVertex3f(-0.125,-0.1,-0.25);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0,0.058/sqrt(0.058*0.058+0.063*0.063),0.063/sqrt(0.058*0.058+0.063*0.063));
    glVertex3f(-0.125,-0.1,-0.25);
    glVertex3f(0.125,-0.1,-0.25);
    glVertex3f(0.25,0.25,-0.48);
    glVertex3f(-0.25,0.25,-0.48);

    glNormal3f(-0.063/sqrt(0.031*0.031+0.063*0.063+0.063*0.063),0.063/sqrt(0.031*0.031+0.063*0.063+0.063*0.063),0.031/sqrt(0.031*0.031+0.063*0.063+0.063*0.063));
    glVertex3f(0.125,-0.1,-0.25);
    glVertex3f(0.25,-0.1,0);
    glVertex3f(0.5,0.25,0);
    glVertex3f(0.25,0.25,-0.48);

    glNormal3f(-0.063/sqrt(0.06*0.06+0.063*0.063+0.031*0.031),0.06/sqrt(0.06*0.06+0.063*0.063+0.031*0.031),-0.031/sqrt(0.06*0.06+0.063*0.063+0.031*0.031));
    glVertex3f(0.25,-0.1,0);
    glVertex3f(0.125,-0.1,0.25);
    glVertex3f(0.25,0.25,0.48);
    glVertex3f(0.5,0.25,0);

    glNormal3f(0,0.058/sqrt(0.058*0.058+0.063*0.063),-0.063/sqrt(0.058*0.058+0.063*0.063));
    glVertex3f(0.125,-0.1,0.25);
    glVertex3f(-0.125,-0.1,0.25);
    glVertex3f(-0.25,0.25,0.48);
    glVertex3f(0.25,0.25,0.48);

    glNormal3f(0.063/sqrt(0.063*0.063+0.063*0.063+0.031*0.031),-0.063/sqrt(0.063*0.063+0.063*0.063+0.031*0.031),-0.031/sqrt(0.063*0.063+0.063*0.063+0.031*0.031));
    glVertex3f(-0.125,-0.1,0.25);
    glVertex3f(-0.25,-0.1,0);
    glVertex3f(-0.5,0.25,0);
    glVertex3f(-0.25,0.25,0.48);

    glNormal3f(0.063/sqrt(0.063*0.063+0.06*0.06+0.031*0.031),0.06/sqrt(0.063*0.063+0.06*0.06+0.031*0.031),0.031/sqrt(0.063*0.063+0.06*0.06+0.031*0.031));
    glVertex3f(-0.25,-0.1,0);
    glVertex3f(-0.125,-0.1,-0.25);
    glVertex3f(-0.25,0.25,-0.48);
    glVertex3f(-0.5,0.25,0);
    glEnd();

    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiante);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, speculaire);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    // croix de cylindres
    glPushMatrix();
    glRotatef(rot, 0,1,0);
    glTranslatef(-4.0f, 0.0f, 0.0f);
    glRotated(90.0, 0., 1., 0.);
    gluCylinder(m_Station, 0.25, 0.25, 8.0, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rot, 0,1,0);
    glTranslatef(0.f, 0.f, -4.0f);
    gluCylinder(m_Station, 0.25, 0.25, 8.0, 32, 32);
    glPopMatrix();

    // le disque supérieur
    glPushMatrix();
    glRotatef(rot, 0,1,0);
    glTranslatef(0.f, 0.3f, 0.0f);
    glRotated(90.0, 1.,0 , 0.);
    gluQuadricOrientation(m_Station, GLU_INSIDE);
    gluCylinder(m_Station, 4, 4, 0.6, 28, 2);//Cylindre interieur
    gluQuadricOrientation(m_Station, GLU_OUTSIDE);
    gluCylinder(m_Station, outerRadius,outerRadius,0.6,28,2);//Cylindre exterieur
    glRotatef(180,0,1,0);
    gluDisk(m_Station, 4, outerRadius, 28, 2);
    glPopMatrix();

    // le disque inférieur
    glPushMatrix();
    glRotatef(rot, 0,1,0);
    glTranslatef(0.f, -0.3f, 0.0f);
    glRotated(90.0, 1.,0 , 0.);
    gluDisk(m_Station, 4, outerRadius, 28, 2);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glPopMatrix();
    glColor3f(1,1,1);

    if(int(10*rot)%100<50){
        glEnable(GL_LIGHT1);
    } else {
        glDisable(GL_LIGHT1);
    }
}
