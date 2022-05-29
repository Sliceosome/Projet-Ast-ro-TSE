#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>

#ifndef ASTEROIDE_H
#define ASTEROIDE_H


class asteroide
{
public:
    // Constructeur avec parametres
    asteroide(int x,int y,int z, int radius);

    // Destructeur
    ~asteroide();

    // Methode d'affichage
    void Display(uint64_t iTimeElapsed) const;

    int getx() { return this->x;};
    int gety(){ return this->y;};
    int getz(){ return this->y;};
    int getradius(){ return this->radius;};

private:
    int x;
    int y;
    int z;
    int radius;
    GLUquadricObj *pObj = gluNewQuadric();
};

#endif // ASTEROIDE_H
