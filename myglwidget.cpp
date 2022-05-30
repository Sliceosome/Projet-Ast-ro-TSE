#include "myglwidget.h"
#include <QApplication>
#include <QInputDialog>
#include <QThread>
#include <cmath>
#include <algorithm>
#include <iostream>


// Declarations des constantes
const unsigned int WIDTH = 641;
const unsigned int HEIGHT = 391;


// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent/*, Webcam* camera*/) : QOpenGLWidget(parent)
{
    bool ok = false;
    nbAste = QInputDialog::getInt(this,"Nombre d'astéroide", "Entrez le nombre d'astéroide (entre 0 et 32) :", 0, 0, 32, 1, &ok);
 //   camera_ = camera;

    // Reglage de la taille/position
    setFixedSize(WIDTH, HEIGHT);

    // Connexion du timer
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += 1.0f;
        update();
    });

    m_AnimationTimer.setInterval(20);
    m_AnimationTimer.start();
}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    setFocusPolicy( Qt::StrongFocus );
    // Reglage de la couleur de fond
    glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);

    // Activation de la lumière
    glEnable(GL_LIGHTING);

    maVoiture = new Vaisseau(0,-1,-5);

    std::list<asteroide*> lstAsteroide = generateastéroides(nbAste);

    // /!\Générer les coordonnées au hasard
    int stationx = rand()%(100 + 1) -50;
    int stationy = rand()%(100 + 1) -50;
    station->setx(0);
    station->sety(0);
}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
       glFrustum(-5, 5, -5, 5, 2, 2000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyGLWidget::setAngle(){
    if(ordre == "right" || ordre == "left"){
        if(ordre == "right")
            this->angleY--;
        else
            this->angleY++;
    }if(ordre == "high" || ordre == "low"){
        if(ordre == "high")
            this->angleX++;
        else
            this->angleX--;
    }if(ordre == "advance"){
        this->profondeurZ--;
    }
}

void MyGLWidget::readOrder(){
    //std::cout << ordre.toStdString() << std::endl;
        glPushMatrix();
        setAngle();
        glRotated(this->angleX,1,0,0);
        glRotated(this->angleY,0,1,0);
        glTranslatef(0,0,this->profondeurZ);
        maVoiture->Display();
        glPopMatrix();
}

// Fonction d'affichage
void MyGLWidget::paintGL()
{
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Definition de la position de la camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 1.f,10.f, 0.0f, -1.0f, -5.0f, 0.0f, 1.0f, 0.0f);

    // Afficher les astéroides + vérif des collisions
    std::list<asteroide*>::iterator it;
    int i = 0;
    for (it = lstAsteroide.begin(); it != lstAsteroide.end(); it++)
    {
        glPushMatrix();
        (*it)->Display(m_TimeElapsed);
        i++;
        glPopMatrix();

        if ( ifCollisionAste((*it)))
        {
            qDebug() << "DEFAITE";
            reset();
        }
    }

    // Affichage de la voiture
    readOrder();

    //Affichage de la station
    glPushMatrix();
    station->Display(m_TimeElapsed);
    glPopMatrix();

    if ( ifFinDePartie() )
    {
        qDebug() << "VICTOIRE";
        reset();

    }


}

std::list<asteroide*> MyGLWidget::generateastéroides(int nbmaxAste)
{

    int nbAsteroide = 0;

    while( nbAsteroide != nbmaxAste)
    {
        int x = rand()%(100 + 1) -50;
        int y = rand()%(100 + 1) -50;
        int z = rand()%(100 + 1) -100;
        int radius = rand()%(5 + 1) + 3; // 3<=radius<=8

        std::list<asteroide*>::iterator it;
        bool flag = true;
        for (it = lstAsteroide.begin(); it != lstAsteroide.end(); it++)
        {
            int iteratorx = (*it)->getx();
            int iteratory = (*it)->gety();
            int iteratorz = (*it)->getz();
            int iteratorradius = (*it)->getradius();
            // Vérifiacation qu'on ne va pas créer 2 astéroides qui se collisionnent
            double distance = pow(pow(iteratorx-x,2)+pow(iteratory-y,2)+pow(iteratorz-z,2),0.5);
            if (distance < iteratorradius + radius)
            {
                flag = false;
            }
        }
        // Vérification que l'astéroide n'apparait pas au meme endroit que le vaisseau
        double distance = pow(pow(x,2)+pow(y,2)+pow(z,2),0.5);
        if (distance < radius) //Vérif distance entre le centre et l'astéroide
        {
            flag = false;
        }

        if (flag == true)
        {
            asteroide *aste = new asteroide(x,y,z,radius);
            lstAsteroide.push_back(aste);
            nbAsteroide += 1;
        }

    }
    qDebug() <<"Fin génération astéroides";

    return lstAsteroide;
}

bool MyGLWidget::ifCollisionAste(asteroide* aste)
{
    //distance = sqrt[(Xa-Xb)²+(Ya-Yb)²+(Za-Zb)²]
    double distance = pow(pow(maVoiture->getx()-aste->getx(),2)+pow(maVoiture->gety()-aste->gety(),2)+pow(maVoiture->getz()-aste->getz(),2),0.5);
    if (distance < (maVoiture->getradius() + aste->getradius()))
    {
        qDebug() << "Vaisseau.x = " << maVoiture->getx() << "Vaisseau.y = " << maVoiture->gety() << "Vaisseau.z = " << maVoiture->getz() ;
        qDebug() << "Aste.x = " << aste->getx() << "Aste.y = " << aste->gety() << "Aste.z = " << aste->getz() << "Aste.radius = " << aste->getradius();
        qDebug() << distance;
        return true;
    }
    return false;
}

bool MyGLWidget::ifFinDePartie()
{
    double distance = pow(pow(maVoiture->getx()-station->getx(),2)+pow(maVoiture->gety()-station->gety(),2)+pow(maVoiture->getz()-station->getz(),2),0.5);
    if (distance < (maVoiture->getradius() + 9))
    {
        qDebug() << "Vaisseau.x = " << maVoiture->getx() << "Vaisseau.y = " << maVoiture->gety() << "Vaisseau.z = " << maVoiture->getz() ;
        qDebug() << "Station.x = " << station->getx() << "Aste.y = " << station->gety() << "Aste.z = " << station->getz();
        qDebug() << distance;
        return true;
    }
    return false;
}rn false;
}

void MyGLWidget::reset()
{
    qDebug() << "reset";

    int stationx = rand()%(100 + 1) -50;
    int stationy = rand()%(100 + 1) -50;

    station->setx(0);
    station->sety(2);
    station->setz(-20);

    maVoiture->setx(0);
    maVoiture->sety(-1);
    maVoiture->setz(-3);

    lstAsteroide.clear();
    generateastéroides(nbAste);

}

