#include "webcam.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/opencv.hpp"

#include <cstdio>
#include <iostream>
#include <QDebug>

using namespace cv;
using namespace std;

Webcam::Webcam(QWidget *parent)
    : QWidget{parent}, cap_(0)
{
    cap_.set(cv::CAP_PROP_FRAME_WIDTH,640);
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT,360);
    std::cout<<"width: "<<cap_.get(cv::CAP_PROP_FRAME_WIDTH)<<std::endl;
    std::cout<<"height: "<<cap_.get(cv::CAP_PROP_FRAME_HEIGHT)<<std::endl;
    if(!cap_.isOpened())  // check if we succeeded
    {
        std::cerr<<"Error openning the default camera"<<std::endl;
    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateVideo()));
    timer->start(5);

}
QPixmap Webcam::Mat2QPixmap(const cv::Mat& mat) {
    cv::Mat rgb;
    QPixmap p;
    //cout << "taille : " << mat.rows << endl;
    cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
    p.convertFromImage(QImage((const unsigned char*)(rgb.data), mat.cols, mat.rows, QImage::Format_RGB888));
    return p;
}

QString Webcam::getOrdre(){return ordre_;}

void Webcam::setOrdre(QString ordre){ordre_ = ordre;}


void Webcam::updateVideo()
{
    cv::Mat frame,frame_gray;
    cap_ >> frame; // get a new frame from camera
    frame_ = frame;
   // std::cout << "taille_avant : " << frame_.rows << std::endl;

    std::vector<Rect> faces;
    // Get frame
    // Mirror effect
    cv::flip(frame,frame,1);
    // Convert to gray
    cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
    // Equalize graylevels
    // equalizeHist( frame_gray, frame_gray );
    CascadeClassifier face_cascade;
    if( !face_cascade.load( "../Projet-Ast-ro-TSE/closed_frontal_palm.xml" ) )
    {
        cerr<<"Error loading haarcascade"<<endl;
        return;
    }
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 4, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );

    if (faces.size()>0)
    {
        // Draw green rectangle
        for (int i=0;i<(int)faces.size();i++)
        {
            rectangle(frame,faces[i],Scalar(0,255,0),2);
            //qDebug() << "top left :" << faces[i].x << "," << faces[i].y;
        }
        if (faces.size() == 2)
        {

            // detect which face is the left fist
            int left;
            int right;
            int delta = 20;

            if (faces[0].x < faces[1].x)
            {
                left = 0;
                right = 1;
            }else{
                left = 1;
                right = 0;
            }

            if (faces[left].y > faces[right].y-delta && faces[left].y < faces[right].y+delta)
            {
                // Both fist are at the same level
                qDebug() << "same level";
                this->ordre_="neutral";

            }else if (faces[left].y > faces[right].y + delta)
            {
                // Left fist is above right (turn left)
                qDebug() << "turn left";
                this->ordre_="left";
            }else if (faces[right].y > faces[left].y + delta)
            {
                // Right fist is above left (turn right)
                qDebug() << "turn right";
                this->ordre_="right";
            }
        }else{
            // Didn't detect 2 fist so back to neutral posi
            qDebug() << "no 2 fist -> back to neutral posi";
            this->ordre_="neutral";

        }

    }

}

cv::Mat Webcam::GetFrame(){
//    std::cout << "taille_après : " << frame_.cols << std::endl;

    return frame_;
}
