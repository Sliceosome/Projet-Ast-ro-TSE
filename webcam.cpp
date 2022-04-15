#include "webcam.h"

Webcam::Webcam(QWidget *parent)
    : QWidget{parent}, cap_(0)
{
    cap_.set(cv::CAP_PROP_FRAME_WIDTH,10000);
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT,10000);
    std::cout<<"max width: "<<cap_.get(cv::CAP_PROP_FRAME_WIDTH)<<std::endl;
    std::cout<<"max height: "<<cap_.get(cv::CAP_PROP_FRAME_HEIGHT)<<std::endl;
    cap_.set(cv::CAP_PROP_FRAME_WIDTH,640);
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT,480);
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

void Webcam::updateVideo()
{
    cv::Mat frame;
    cap_ >> frame; // get a new frame from camera
    frame_ = frame;
   // std::cout << "taille_avant : " << frame_.rows << std::endl;

}

cv::Mat Webcam::GetFrame(){
    //std::cout << "taille_après : " << frame_.rows << std::endl;
    return frame_;
}
