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
    MainWindow(QWidget *parent = nullptr);  //Constructeur
    ~MainWindow();  //Destructeur

private slots:
    void update_all();      //Slot pour l'update de tout le jeu (le widget OpenGL et la Webcam)

private:
    Ui::MainWindow *ui; //Eléments nécessaires à la classe
    Webcam *camera_;
    MyGLWidget *GlWidget;
};
#endif // MAINWINDOW_H
