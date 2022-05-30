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

    void setProf(float prof_){prof=prof_;}
    void setTheta(float theta_){theta=theta_;}
    void setPhi(float phi_){phi=phi_;}



    void turn(QString ordre);
    // Methode d'affichage

    int getx();
    int getx_gauche() { return this->x;};
    int gety();
    int getz();
    int getradius(){ return this->radius;};

    float getProf(){return prof;}
    float getTheta(){return theta;}
    float getPhi(){return phi;}


private:
    GLUquadric * m_Roue { nullptr };
    GLUquadric * m_Roue2 { nullptr };

    float x = -3.f;
    float y = -1.f;
    float z = -5.f;
    float prof = 0;
    float theta = 0;
    float phi = 0;

    int radius = 6;
};
#endif // VAISSEAU_H
