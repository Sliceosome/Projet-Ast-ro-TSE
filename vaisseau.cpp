#include "vaisseau.h"

Vaisseau::Vaisseau()
{
    // Initialisation des paramètres
    m_Roue = gluNewQuadric();
}

Vaisseau::~Vaisseau()
{
    // Destruction de la quadrique
    if(m_Roue)
        gluDeleteQuadric(m_Roue);
}

void Vaisseau::Display(uint64_t iTimeElapsed) const
{
    // Vaisseau

    GLfloat light_tab[] = {0.25, 0.25, 0.25,0.25};
    GLfloat light_tab2[] = {0.4, 0.4, 0.4,0.4};
    GLfloat light_tab3[] = {0.774597, 0.774597, 0.774597,0.774597};

    float shininess = 76.8f;

    GLfloat light_tab4[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_tab5[] = {0.0f, 4.f, 4.f, 1.0};
    GLfloat light_tab7[] = {-0.75f, -0.75f, 0.1f};
    GLfloat light_tab8[] = {0.75f, -0.75f, 0.1f};



    GLfloat jaune[] = {1.f, 1.0, 0.0, 1.0};

    glLightfv(GL_LIGHT0,GL_POSITION,light_tab5);
    glLightfv(GL_LIGHT0,GL_AMBIENT, light_tab4);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, light_tab4);
    glLightfv(GL_LIGHT0,GL_SPECULAR, light_tab4);


    glMaterialfv(GL_FRONT,GL_AMBIENT, light_tab);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, light_tab2);
    glMaterialfv(GL_FRONT,GL_SPECULAR, light_tab3);
    glMaterialf(GL_FRONT,GL_SHININESS, shininess);


    glBegin(GL_QUADS);
    glColor3ub(100, 0, 0);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-1.f, -1.f, 0.f);
    glVertex3f(1.f, -1.f, 0.f);
    glVertex3f(1.f, 1.f, 0.f);
    glVertex3f(-1.f, 1.f, 0.f);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-1.f, 1.f, 0.f);
    glVertex3f(1.f, 1.f, 0.f);
    glVertex3f(1.f, 1.f, -3.f);
    glVertex3f(-1.f, 1.f, -3.f);

    glNormal3f(0.0,-1.0,0.0);
    glVertex3f(-1.f, -1.f, 0.f);
    glVertex3f(1.f, -1.f, 0.f);
    glVertex3f(1.f, -1.f, -3.f);
    glVertex3f(-1.f, -1.f, -3.f);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(1.f, 1.f, 0.f);
    glVertex3f(1.f, -1.f, 0.f);
    glVertex3f(1.f, -1.f, -3.f);
    glVertex3f(1.f, 1.f, -3.f);

    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(-1.f, 1.f, 0.f);
    glVertex3f(-1.f, -1.f, 0.f);
    glVertex3f(-1.f, -1.f, -3.f);
    glVertex3f(-1.f, 1.f, -3.f);

    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(-1.f, -1.f, -3.f);
    glVertex3f(1.f, -1.f, -3.f);
    glVertex3f(1.f, 1.f, -3.f);
    glVertex3f(-1.f, 1.f, -3.f);
    glEnd();

    // Wheels
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(1.f, -1.f, -0.5f);
    glRotated(90.0, 0., 1., 0.);
    gluCylinder(m_Roue, 0.5, 0.5, 0.3, 32, 32);
    glTranslatef(0.f, 0.f, 0.3f);
    gluDisk(m_Roue, 0.0, 0.5, 30, 1);
    glRotatef(180.f, 1.f, 0.f, 0.f);
    gluDisk(m_Roue, 0.0, 0.5, 30, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.3f, -1.f, -0.5f);
    glRotated(90.0, 0., 1., 0.);
    gluCylinder(m_Roue, 0.5, 0.5, 0.3, 32, 32);
    gluDisk(m_Roue, 0.0, 0.5, 30, 1);
    glRotatef(180.f, 1.f, 0.f, 0.f);
    gluDisk(m_Roue, 0.0, 0.5, 30, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.f, -1.f, -2.5f);
    glRotated(90.0, 0., 1., 0.);
    gluCylinder(m_Roue, 0.5, 0.5, 0.3, 32, 32);
    glTranslatef(0.f, 0.f, 0.3f);
    gluDisk(m_Roue, 0.0, 0.5, 30, 1);
    glRotatef(180.f, 1.f, 0.f, 0.f);
    gluDisk(m_Roue, 0.0, 0.5, 30, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.3f, -1.f, -2.5f);
    glRotated(90.0, 0., 1., 0.);
    gluCylinder(m_Roue, 0.5, 0.5, 0.3, 32, 32);
    gluDisk(m_Roue, 0.0, 0.5, 30, 1);
    glRotatef(180.f, 1.f, 0.f, 0.f);
    gluDisk(m_Roue, 0.0, 0.5, 30, 1);
    glPopMatrix();

    if(iTimeElapsed%10 == 0){
        glPushMatrix();
        gluQuadricDrawStyle(m_Roue,GLU_FILL);
        glNormal3f(0.0,0.0,1.0);

        glLightfv(GL_LIGHT1,GL_POSITION,light_tab7);
        glLightfv(GL_LIGHT2,GL_POSITION,light_tab8);
        glLightfv(GL_LIGHT1,GL_DIFFUSE, jaune);
        glLightfv(GL_LIGHT2,GL_DIFFUSE, jaune);

        glMaterialfv(GL_FRONT,GL_DIFFUSE, jaune);

        glTranslatef(-0.75f, -0.75f, 0.1f);
        gluDisk(m_Roue, 0.0, 0.25, 30, 1);
        glTranslatef(1.5f, 0.f, 0.f);
        gluDisk(m_Roue, 0.0, 0.25, 30, 1);
        glPopMatrix();
    }
}
