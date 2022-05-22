#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QtMath>
#include <QTimer>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include "myglwidget.h"
#include <mutex>
#include <thread>
#include "endgamedialog.h"

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QRect  screenGeometry= QGuiApplication::primaryScreen()->geometry();
    height = screenGeometry.height();
    width = screenGeometry.width();

    ui->setupUi(this);
    ui->camera->setFixedWidth(width/2 - 30);
    ui->camera->setFixedHeight(height/2);
    ui->camera->move(width/2+20,height/4-60);
    ui->timerLabel->move(width/2+20, 30);
    ui->quitButton->move(width-160, height-140);

    cap=VideoCapture(0);
    cap.set(3, 1280);
    cap.set(4, 720);

    timer = new QTimer(this);
    chrono=new QElapsedTimer();
    chrono->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(displayWebcam()));
    connect(timer,SIGNAL(timeout()),this,SLOT(displayTimer()));
    timer->start(20);

    connect(this, SIGNAL(asteroidsChange(int)), ui->glWidget, SLOT(asteroidsChange(int)));
    connect(ui->glWidget, SIGNAL(endOfGame(bool)), this, SLOT(openEndOfGameDialog(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * function that listens to key press and computes
 * movement of the space ship
 * @brief MainWindow::keyPressEvent
 * @param event key pressed
 */
void MainWindow::keyPressEvent(QKeyEvent* event){
    switch(event->key()){
    default: {
        event->ignore();
        return;
    }
    case Qt::Key_D: {
        ui->glWidget->computeMovement(0);
        break;
    }
    case Qt::Key_Q: {
        ui->glWidget->computeMovement(1);
        break;
    }
    case Qt::Key_I: {
        ui->glWidget->computeMovement(2);
        break;
    }
    case Qt::Key_K: {
        ui->glWidget->computeMovement(3);
        break;
    }
    case Qt::Key_Z: {
        ui->glWidget->computeMovement(4);
        break;
    }
    case Qt::Key_S: {
        ui->glWidget->computeMovement(5);
        break;
    }
    }
    event->accept();
}


/**
 * Function to display camera
 */
void MainWindow::displayWebcam()
{
    Mat frame;
    Mat frameGray;
    vector<Rect> hands;
    cap >> frame; // get frame

    flip(frame, frame, 1); // mirror reverse

    cvtColor(frame, frameGray, COLOR_BGR2GRAY); // convert to gray

    // display in frame
    Mat frameToDisplay;
    frame.copyTo(frameToDisplay);
    QImage qImage(frameToDisplay.data, frameToDisplay.cols, frameToDisplay.rows, frameToDisplay.step, QImage::Format_BGR888);
    QPixmap qPix=QPixmap::fromImage(qImage);
    ui->camera->setPixmap(qPix.scaled(width/2, height/2, Qt::KeepAspectRatio));
    //ui->camera->setPixmap(qPix);



    //    hand_cascade.detectMultiScale(frameGray, hands, 1.1, 4, 0, Size(60,60)); // hands detection
    //    if(hands.size()>0 && hands.size()<3){

    //        // draw green rectangles
    //        for (int i=0;i<(int)hands.size();i++)
    //            rectangle(frame,hands[i],Scalar(0,255,0),2);
    //    }






}


/**
 * function to display timer on frame
 */
void MainWindow::displayTimer()
{
    if(chrono->elapsed()/1000==60){
        minutes+=1;
        chrono->restart();
    }
    if(minutes!=0){
        time=QString::number(minutes)+" min "+QString::number(chrono->elapsed()/1000)+" s";
    }else{
        time=QString::number(chrono->elapsed()/1000)+" s";
    }
    ui->timerLabel->setText("Timer : "+time);
}

/**
 * slot that closes window to go back to menu window
 */
void MainWindow::on_quitButton_clicked()
{
    this->close();
    emit openMenuWindow();
}

/**
 * slot that stops game and open end of game dialog
 * @param result of the game
 */
void MainWindow::openEndOfGameDialog(bool result)
{
    timer->stop();

    bool gameWon=result;
    QString message, title;
    if(gameWon){
        message=QString("You arrived safe and sound at the space station.");
        title=QString("Success!");
    }else{
        message=QString("Your space ship collided into an asteroid and you are now lost in outer space...");
        title=QString("Game Over");
    }
    QString score=QString("Your time : "+ time);

    EndGameDialog dialog(title, message, score, this);
    int code = dialog.exec();

    if(code==0 || code == 1){
        this->close();
        emit openMenuWindow();
    }
}
