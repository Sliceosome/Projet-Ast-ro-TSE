#include "asteroide.h"
#include <GL/glext.h>
#include <GL/gl.h>
#include <QDir>
#include <QBitmap>

asteroide::asteroide(int x,int y, int z, int radius)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;

    pObj = gluNewQuadric();

    image->load(QDir::currentPath()+"/../Projet-Ast-ro-TSE/aste.png");
    QImage imageOpenGL = image->convertToFormat(QImage::Format_RGBA8888);

}

asteroide::~asteroide()
{
    // Destruction de la quadrique
    if(this->pObj)
        gluDeleteQuadric(this->pObj);
}

void asteroide::Display(uint64_t iTimeElapsed) const
{
    glEnable(GL_TEXTURE_2D);

    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexImage2D(GL_TEXTURE_2D,0,3,image->width(),image->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image->bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    gluQuadricDrawStyle(pObj,GLU_FILL);
    gluQuadricTexture(pObj,GL_TRUE);
    glColor3ub(120,120,120);

    glTranslatef(x,y,z);
    gluSphere(pObj, radius, 25, 25);

    glDisable(GL_TEXTURE_2D);

}
