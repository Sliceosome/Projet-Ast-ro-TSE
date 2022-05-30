#include "station.h"
#include <QBitmap>
#include <GL/glext.h>
#include <GL/gl.h>
#include <QDir>


Station::Station(int x, int y, int z)
{
    glEnable(GL_LIGHT1);
    corps = gluNewQuadric();

    this->x = x;
    this->y = y;
    this->z = z;

    GLfloat light_tab[] = {0.4, 0.4, 0.4,0.25};
    GLfloat light_tab2[] = {0.4, 0.4, 0.4,0.4};
    GLfloat light_tab3[] = {0.774597, 0.774597, 0.774597,0.774597};

    float shininess = 76.8f;

    GLfloat light_tab4[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_tab5[] = {0.0f, 4.f, 4.f, 1.0};
    GLfloat light_tab7[] = {-0.75f, -0.75f, 0.1f};
    GLfloat light_tab8[] = {0.75f, -0.75f, 0.1f};

    GLfloat jaune[] = {1.f, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT1,GL_POSITION,light_tab5);
    glLightfv(GL_LIGHT1,GL_AMBIENT, light_tab4);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, light_tab4);
    glLightfv(GL_LIGHT1,GL_SPECULAR, light_tab4);


    glMaterialfv(GL_FRONT,GL_AMBIENT, light_tab);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, light_tab2);
    glMaterialfv(GL_FRONT,GL_SPECULAR, light_tab3);
    glMaterialf(GL_FRONT,GL_SHININESS, shininess);
}


void Station::Display(uint64_t iTimeElapsed) const
{

    gluQuadricDrawStyle(corps,GLU_FILL);

    //Corps de la station
    glPushMatrix();

    glColor3ub(110, 110, 110);
    glTranslatef(this->x, this->y, this->z);
    glRotated(90.0, 0., 1., 0.);
    gluCylinder(corps, 2, 2, 4, 32, 32);
    gluDisk(corps, 0.0, 2, 30, 1);
    glTranslatef(0.f, 0.f, 4.f);
    gluDisk(corps, 0.0, 2, 30, 1);
    gluCylinder(corps, 1, 1, 3, 32, 32);
    glTranslatef(0.f, 0.f, 3.f);
    gluDisk(corps, 0.0, 2, 30, 1);
    gluCylinder(corps, 2, 2, 4, 32, 32);
    glTranslatef(0.f, 0.f, 4.f);
    gluDisk(corps, 0.0, 2, 30, 1);
    gluCylinder(corps, 1, 1, 3, 32, 32);
    glTranslatef(0.f, 0.f, 3.f);
    gluDisk(corps, 0.0, 2, 30, 1);
    gluCylinder(corps, 2, 2, 4, 32, 32);

    glPopMatrix();
    //Panneau solaire
    glPushMatrix();

    glTranslatef(this->x,this->y,this->z);
    glRotatef(iTimeElapsed%360,1,0,0);
    glTranslatef(-this->x,-this->y,-this->z);

    glBegin(GL_QUADS);
    glColor3ub(0, 0, 100);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(this->x+1,this->y,this->z);
    glVertex3f(this->x+1,this->y+8,this->z);
    glVertex3f(this->x+3,this->y+8,this->z);
    glVertex3f(this->x+3,this->y,this->z);

    glVertex3f(this->x+1,this->y,this->z);
    glVertex3f(this->x+1,this->y-8,this->z);
    glVertex3f(this->x+3,this->y-8,this->z);
    glVertex3f(this->x+3,this->y,this->z);

    glVertex3f(this->x+8,this->y,this->z);
    glVertex3f(this->x+8,this->y+8,this->z);
    glVertex3f(this->x+10,this->y+8,this->z);
    glVertex3f(this->x+10,this->y,this->z);

    glVertex3f(this->x+8,this->y,this->z);
    glVertex3f(this->x+8,this->y-8,this->z);
    glVertex3f(this->x+10,this->y-8,this->z);
    glVertex3f(this->x+10,this->y,this->z);

    glVertex3f(this->x+15,this->y,this->z);
    glVertex3f(this->x+15,this->y+8,this->z);
    glVertex3f(this->x+17,this->y+8,this->z);
    glVertex3f(this->x+17,this->y,this->z);

    glVertex3f(this->x+15,this->y,this->z);
    glVertex3f(this->x+15,this->y-8,this->z);
    glVertex3f(this->x+17,this->y-8,this->z);
    glVertex3f(this->x+17,this->y,this->z);
    glEnd();

    glPopMatrix();
    //Logo de télécom
    glPushMatrix();
    glTranslatef(this->x+8, this->y-1, this->z+2);

    glColor3ub(255, 255, 255);

    glEnable(GL_TEXTURE_2D);
    QImage* image = new QImage();
    image->load(QDir::currentPath()+"/../Projet-Ast-ro-TSE/sigle_telecom_350.png");
    QImage imageOpenGL = image->convertToFormat(QImage::Format_RGBA8888);
    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexImage2D(GL_TEXTURE_2D,0,3,image->width(),image->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image->bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBegin(GL_QUADS);
    glTexCoord2f(1,1); glVertex2f(0,0);
    glTexCoord2f(1,0); glVertex2f(0,2);
    glTexCoord2f(0,0); glVertex2f(2,2);
    glTexCoord2f(0,1); glVertex2f(2,0);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    if(iTimeElapsed%10 == 0){
        glPushMatrix();
        glTranslatef(this->x+9, this->y+2, this->z+2);

        gluQuadricDrawStyle(corps,GLU_FILL);
        glNormal3f(0.0,0.0,1.0);

        glLightfv(GL_LIGHT1,GL_POSITION,light_tab7);
        glLightfv(GL_LIGHT2,GL_POSITION,light_tab8);
        glLightfv(GL_LIGHT1,GL_DIFFUSE, jaune);
        glLightfv(GL_LIGHT2,GL_DIFFUSE, jaune);

        glMaterialfv(GL_FRONT,GL_DIFFUSE, jaune);

        glTranslatef(-0.75f, -0.75f, 0.1f);
        gluDisk(corps, 0.0, 0.25, 30, 1);
        glTranslatef(1.5f, 0.f, 0.f);
        gluDisk(corps, 0.0, 0.25, 30, 1);
        glPopMatrix();
    }
    glDisable(GL_LIGHT1);
}
