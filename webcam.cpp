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

Webcam::Webcam(QWidget *parent, MyGLWidget *gl)
    : QWidget{parent}, cap_(0)
{
    gl_ = gl;
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


void Webcam::updateVideo()
{
    cv::Mat frame,frame_gray;
    cap_ >> frame; // get a new frame from camera
    frame_ = frame;
   // std::cout << "taille_avant : " << frame_.rows << std::endl;

    std::vector<Rect> fists;
    std::vector<Rect> palms;
    // Get frame
    // Mirror effect
    cv::flip(frame,frame,1);
    // Convert to gray
    cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
    // Equalize graylevels
    // equalizeHist( frame_gray, frame_gray );
    CascadeClassifier face_cascade_fist;
    CascadeClassifier face_cascade_palm;

    if( !face_cascade_fist.load( "./fist_v3.xml" ) )
    {
        cerr<<"Error loading haarcascade fist"<<endl;
        return;
    }
    if( !face_cascade_palm.load( "./palm_v4.xml" ) )
    {
        cerr<<"Error loading haarcascade palm"<<endl;
        return;
    }
    //-- Detect faces
    face_cascade_fist.detectMultiScale( frame_gray, fists, 1.1, 4, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );
    face_cascade_palm.detectMultiScale( frame_gray, palms, 1.1, 4, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );

    if (fists.size()>0 || palms.size() > 0)
    {
        // Draw green rectangle
        for (int i=0;i<(int)fists.size();i++)
        {
            rectangle(frame,fists[i],Scalar(0,255,0),2);
            //qDebug() << "top left :" << faces[i].x << "," << faces[i].y;
        }
        for (int i=0;i<(int)palms.size();i++)
        {
            rectangle(frame,palms[i],Scalar(0,255,0),2);
            //qDebug() << "top left :" << faces[i].x << "," << faces[i].y;
        }
        if(palms.size() == 2){
            int left_p;
            int right_p;
            int delta_p = 20;
            if (palms[0].x < palms[1].x)
            {
                left_p = 0;
                right_p = 1;
            }else{
                left_p = 1;
                right_p = 0;
            }
            if (palms[left_p].y > palms[right_p].y-delta_p && palms[left_p].y < palms[right_p].y+delta_p)
            {
                // Both palms are at the same level
                //qDebug() << "palms same level";
                this->ordre_="advance";
            }
        }
        else if (fists.size() == 2)
        {

            // detect which face is the left fist
            int left;
            int right;
            int delta = 20;

            if (fists[0].x < fists[1].x)
            {
                left = 0;
                right = 1;
            }else{
                left = 1;
                right = 0;
            }

            if (fists[left].y > fists[right].y-delta && fists[left].y < fists[right].y+delta)
            {
                if(fists[left].y > 150+delta){
                    this->ordre_= "low";

                }else if(fists[left].y < 150-3*delta){
                    this->ordre_= "high";

                }else{
                // Both fist are at the same level
                this->ordre_="neutral";}

            }else if (fists[left].y > fists[right].y + delta)
            {
                // Left fist is above right (turn left)
                //qDebug() << "turn left";
                this->ordre_="left";
            }else if (fists[right].y > fists[left].y + delta)
            {
                // Right fist is above left (turn right)
                //qDebug() << "turn right";
                this->ordre_="right";
            }

        }else{
            // Didn't detect 2 fist so back to neutral posi
            //qDebug() << "no 2 fist -> back to neutral posi";
            this->ordre_="neutral";
        }

    }

}

cv::Mat Webcam::GetFrame(){
//    std::cout << "taille_après : " << frame_.cols << std::endl;

    return frame_;
}
