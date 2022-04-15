#ifndef WEBCAM_H
#define WEBCAM_H

#include <QWidget>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <QTimer>


//using namespace cv;
//using namespace std;

class Webcam : public QWidget
{
    Q_OBJECT
public:
    explicit Webcam(QWidget *parent = nullptr);
    QPixmap Mat2QPixmap(const cv::Mat& mat);
    cv::Mat GetFrame();

private slots:
    void updateVideo();


private:
    cv::Mat frame_;
    cv::VideoCapture cap_;
};

#endif // WEBCAM_H
