#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "webcam.h"
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "myglwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void update_all();

private:
    Ui::MainWindow *ui;
    Webcam *camera_;
    MyGLWidget *GlWidget;
    QString ordre_displayed = "neutral";
};
#endif // MAINWINDOW_H
