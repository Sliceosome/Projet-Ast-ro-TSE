#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "vaisseau.h"
#include "asteroide.h"
#include "station.h"
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>

// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget
{
public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr/*, Webcam* camera = nullptr*/);
    void setOrder(QString order){this->ordre = order;}  //Setter de l'ordre de déplacement du vaisseau, en provenance de la webcam
    void setAngle();    //Méthode pour incrémenter/décrémenter le bon angle/la profondeur en fonction de l'ordre qu'on reçoit de la webcam


protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    //Génération des astéroides
    std::list<asteroide*> generateastéroides(int nbmaxAste);

    //Gestion collision astéroide
    bool ifCollisionAste(asteroide* aste);

    //Gestion arrivé à la station
    bool ifFinDePartie();

    void readOrder();   //Rassemble les différentes fonctions de l'affichage du vaisseau pour gérer son déplacement
    
    //Gestion du reset du jeu
    void reset();
    
    //Instant win : aide au débogage
    void keyPressEvent(QKeyEvent *event)
    {
         qDebug() << "key pressed";
         station->setz(maVoiture->getz());
     }

    void setPosCam(float x, float y, float z){  //Utilisée pour set les variables de postion cartésienne de la caméra
        x_ = x;
        y_ = y;
        z_ = z;
    }

private:
    Vaisseau* maVoiture = nullptr;  //Les différents attributs stockés nécessaires.
    int nbAste;
    std::list<asteroide*> lstAsteroide;
    Station* station = new Station(0,0,-20);

    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;
    QString ordre;
    float angleX = 0.f;
    float angleY = 0.f;
    float profondeurZ = 0.f;
    float x_ = 0;
    float y_ = 1;
    float z_ = 10;

};

#endif // MYGLWIDGET_H
