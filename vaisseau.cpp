#include "vaisseau.h"
#include <iostream>


Vaisseau::Vaisseau(int x, int y, int z)
{
    // Initialisation des paramètres
    m_Roue = gluNewQuadric();
    m_Roue2 = gluNewQuadric();

    this->x = x-3;
    this->y = y;
    this->z = z;
}

Vaisseau::~Vaisseau()
{
    // Destruction de la quadrique
    if(m_Roue)
        gluDeleteQuadric(m_Roue);
    if(m_Roue2)
        gluDeleteQuadric(m_Roue2);
}

int Vaisseau::getx(){
    //std::cout <<prof << " et : " << theta << " et : " << phi << std::endl;
    return prof*std::sin((theta*M_PI)/180)*std::cos((phi*M_PI)/180);
}
int Vaisseau::gety(){
    return prof*std::sin((theta*M_PI)/180)*std::sin((phi*M_PI)/180)-1;
}
int Vaisseau::getz(){
    return prof*std::cos((theta*M_PI)/180)-5;
}

void Vaisseau::turn(QString ordre){
    if(ordre == "left"){

    }else if(ordre == "right"){

    }
}

void Vaisseau::Display()
{
    gluQuadricDrawStyle(m_Roue,GLU_FILL);
    glEnable(GL_LIGHT0);
    GLfloat val_lum[] = {1.0, 1.0, 0.0,1.0};
    GLfloat pos_lum[] = {0.0, 0.0, 1.0,0.0};
    GLfloat val_vaiss[] = {1.0, 0.0, 0.0,1.0};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,val_lum);
    glLightfv(GL_LIGHT0,GL_POSITION,pos_lum);


    //Cylindre gauche

    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,val_vaiss);
    glTranslatef(x, y, z);
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
    glVertex3d(x+radius,y+1,z);
    glVertex3d(x+radius,y-1,z);
    glVertex3d(x-2,y-1,z);
    glVertex3d(x-2,y+1,z);
    glEnd();
    //glDisable(GL_LIGHT0);
}
