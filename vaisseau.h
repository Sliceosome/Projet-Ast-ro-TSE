#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>
// Classe dediee pour la gestion de la voiture
class Vaisseau
{
public:
    Vaisseau(int x, int y, int z);
    void Display();
    ~Vaisseau();

    void setx(float x_){this->x=x_-3;}
    void sety(float y_){this->y=y_;}
    void setz(float z_){this->z=z_;}

    void turn(QString ordre);
    // Methode d'affichage

    int getx() { return this->x+3;};
    int getx_gauche() { return this->x;};
    int gety(){ return this->y;};
    int getz(){ return this->z;};
    int getradius(){ return this->radius;};

private:
    GLUquadric * m_Roue { nullptr };
    GLUquadric * m_Roue2 { nullptr };

    float x = -3.f;
    float y = -1.f;
    float z = -5.f;
    int radius = 6;
};
#endif // VAISSEAU_H
