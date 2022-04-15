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
    Vaisseau();

    // Destructeur
    ~Vaisseau();

    // Methode d'affichage
    void Display(uint64_t iTimeElapsed) const;

private:
    GLUquadric * m_Roue { nullptr };
};
#endif // VAISSEAU_H
