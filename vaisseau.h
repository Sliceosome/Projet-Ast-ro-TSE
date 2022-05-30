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
    Vaisseau();     //Constructeur
    void Display(); //Affichage
    ~Vaisseau();    //Destructeur

    void setProf(float prof_){prof=prof_;}  //Profondeur mise à jour du vaisseau, quand les paumes sont alignés
    void setTheta(float theta_){theta=theta_;}  //Angle theta des coordonées sphériques mis à jour, quand on tourne à droite/gauche
    void setPhi(float phi_){phi=phi_;}  //Angle phi des coordonnées sphériques mis à jour, quand on tounr en haut/bas

    float getx();   //Retourne la position cartésienne du vaisseau (x ici)
    float gety();   //Retourne la position cartésienne du vaisseau (y ici)
    float getz();   //Retourne la position cartésienne du vaisseau (z ici)
    float getradius(){ return this->radius;};   //Retourne le rayon de la boule englobante du vaisseau (pour détecter les collisions)

    float getProf(){return prof;}       //getters des coordonnées sphériques
    float getTheta(){return theta;}
    float getPhi(){return phi;}


private:
    GLUquadric * m_Roue { nullptr };    //Les quadriques du vaisseau
    GLUquadric * m_Roue2 { nullptr };

    float prof = 0;     //Initialisation des coordonnées sphériques du vaisseau et du rayon de sa boite englobante
    float theta = 0;
    float phi = 0;

    float radius = 3;
};
#endif // VAISSEAU_H
