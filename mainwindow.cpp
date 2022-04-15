#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Webcam *camera = new Webcam(this);
    camera_ = camera;
    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(update_all()));
    timer2->start(10);
}

void MainWindow::update_all(){
    QPixmap *pixmap = new QPixmap(camera_->Mat2QPixmap(camera_->GetFrame()));
    //*pixmap = pixmap->scaled(cv::CAP_PROP_FRAME_WIDTH, (int)((double)cv::CAP_PROP_FRAME_HEIGHT*(2/3)),Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->label->setPixmap(*pixmap);

};


MainWindow::~MainWindow()
{
    delete ui;
}
