#ifndef STATION_H
#define STATION_H

#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>

class Station
{
public:
    Station(int x, int y, int z);

    void Display(uint64_t iTimeElapsed) const;

    int getx() { return this->x+9;};
    int gety(){ return this->y;};
    int getz(){ return this->z;};
    
    void setx(int newX) {x = newX;};
    void sety(int newY) {y = newY;};
    void setz(int newZ) {z = newZ;};


private:
    GLUquadric * corps { nullptr };

    int x;
    int y;
    int z;

    GLfloat light_tab[3];
    GLfloat light_tab2[3];
    GLfloat light_tab3[3];

    float shininess = 76.8f;

    GLfloat light_tab4[3];
    GLfloat light_tab5[3];
    GLfloat light_tab7[3];
    GLfloat light_tab8[3];

    GLfloat jaune[4];
};

#endif // STATION_H
