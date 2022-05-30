#include "vaisseau.h"
#include <iostream>


Vaisseau::Vaisseau()
{
    // Initialisation des paramètres
    m_Roue = gluNewQuadric();
    m_Roue2 = gluNewQuadric();
}

Vaisseau::~Vaisseau()
{
    // Destruction de la quadrique
    if(m_Roue)
        gluDeleteQuadric(m_Roue);
    if(m_Roue2)
        gluDeleteQuadric(m_Roue2);
}

float Vaisseau::getx(){
    std::cout << (0.000000000001+prof)*std::sin((theta*M_PI)/180)*std::cos((phi*M_PI)/180) << std::endl;
    return (0.000000000001+prof)*std::sin((theta*M_PI)/180)*std::cos((phi*M_PI)/180);
}
float Vaisseau::gety(){
    return (0.000000000001+prof)*std::sin((theta*M_PI)/180)*std::sin((phi*M_PI)/180)-1;
}
float Vaisseau::getz(){
    return (0.000000000001+prof)*std::cos((theta*M_PI)/180)-5;
}

void Vaisseau::Display()
{
    gluQuadricDrawStyle(m_Roue,GLU_FILL);
    glEnable(GL_LIGHT0);
    GLfloat val_lum[] = {1.0, 1.0, 1.0,1.0};
    GLfloat pos_lum[] = {0.0, 0.0, 1.0,0.0};
    GLfloat val_vaiss[] = {1.0, 1.0, 0.0,1.0};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,val_lum);
    glLightfv(GL_LIGHT0,GL_POSITION,pos_lum);


    //Cylindre gauche

    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,val_vaiss);
    glTranslatef(getx()-3, gety()-1, getz()-5);
    glRotated(90.0, 0., 1., 0.);
    gluCylinder(m_Roue, 5, 5, 1, 32, 32);
    glTranslatef(-0.01f, 0.f, 0.f);
    gluDisk(m_Roue2, 0.0, 5, 30, 1);
    glRotated(-90.0, 0., 1., 0.);

    //Cylindre droite

    glTranslatef(6, 0, 0);
    glRotated(90.0, 0., 1., 0.);
    gluCylinder(m_Roue, 5, 5, 1, 32, 32);
    glTranslatef(0.01f,0.f,0.f);
    gluDisk(m_Roue2, 0.0, 5, 30, 1);
    glRotated(-90.0, 0., 1., 0.);

    //rectangle reliant les 2

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glVertex3d(getx()+2,gety()+1,getz());
    glVertex3d(getx()+2,gety()-1,getz());
    glVertex3d(getx()-4,gety()-1,getz());
    glVertex3d(getx()-4,gety()+1,getz());
    glEnd();
    glDisable(GL_LIGHT0);
}
