#ifndef WEBCAM_H
#define WEBCAM_H

#include <QWidget>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <QTimer>
#include "myglwidget.h"

class Webcam : public QWidget
{
    Q_OBJECT
public:
    explicit Webcam(QWidget *parent = nullptr, MyGLWidget *gl= nullptr);    //Constructeur de la webcam
    QPixmap Mat2QPixmap(const cv::Mat& mat);    //Transforme une matrice de OpenCV provenant de la webcam en une image affichée dans l'application
    cv::Mat GetFrame(); //Récupère la frame courante du VidéoCapture
    QString getOrdre(); //getter-setter de l'ordre donnée par OpenCV pour le déplacement du vaisseau
    void setOrdre(QString ordre){this->ordre_=ordre;}


private slots:
    void updateVideo(); //Slot d'update de la frame du VidéoCapture qu'on affiche


private:
    cv::Mat frame_;     //Stockage des différents élements de la classe de la webcam
    cv::VideoCapture cap_;
    QString ordre_;
    MyGLWidget* gl_ = nullptr;
};

#endif // WEBCAM_H
