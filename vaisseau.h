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
    // Constructeur avec parametres
    Vaisseau(int x, int y, int z);

    // Destructeur
    ~Vaisseau();

    void turn(QString ordre);
    // Methode d'affichage
    void Display(uint64_t iTimeElapsed) const;

    int getx() { return this->x;};
    int gety(){ return this->y;};
    int getz(){ return this->y;};
    int getradius(){ return this->radius;};

private:
    GLUquadric * m_Roue { nullptr };

    int x;
    int y;
    int z;
    int radius;
};
#endif // VAISSEAU_H
