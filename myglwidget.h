#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "vaisseau.h"
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include "webcam.h"

// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget
{
public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr, Webcam* camera = nullptr);

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

private:
    Vaisseau* maVoiture = nullptr;
    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;
    Webcam* camera_ = nullptr;
};

#endif // MYGLWIDGET_H
