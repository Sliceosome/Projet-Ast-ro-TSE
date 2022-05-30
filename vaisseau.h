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
    Vaisseau();
    void Display();
    ~Vaisseau();

    void setProf(float prof_){prof=prof_;}
    void setTheta(float theta_){theta=theta_;}
    void setPhi(float phi_){phi=phi_;}

    float getx();
    float gety();
    float getz();
    float getradius(){ return this->radius;};

    float getProf(){return prof;}
    float getTheta(){return theta;}
    float getPhi(){return phi;}


private:
    GLUquadric * m_Roue { nullptr };
    GLUquadric * m_Roue2 { nullptr };

    float prof = 0;
    float theta = 0;
    float phi = 0;

    float radius = 6;
};
#endif // VAISSEAU_H
