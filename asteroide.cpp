#include "asteroide.h"
#include <GL/glext.h>
#include <GL/gl.h>

asteroide::asteroide(int x,int y, int z, int radius)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;

}

asteroide::~asteroide()
{
    // Destruction de la quadrique
    if(this->pObj)
        gluDeleteQuadric(this->pObj);
}

void asteroide::Display(uint64_t iTimeElapsed) const
{
    gluQuadricDrawStyle(this->pObj,GLU_FILL);
    glColor3f(0.5f, 0.5f, 0.5f);

    glTranslatef((GLfloat) this->x,(GLfloat) this->y,(GLfloat) this->z);
    gluQuadricTexture(pObj,GLU_TRUE);
    gluSphere(this->pObj, this->radius, 25, 25);

}
