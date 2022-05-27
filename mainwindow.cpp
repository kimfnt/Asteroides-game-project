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
    cap.set(CAP_PROP_FRAME_WIDTH,1280);
    cap.set(CAP_PROP_FRAME_HEIGHT,720);

    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
    }

    if(!hand_cascade.load("../projet-bdm-asteroides/res/closed_frontal_palm.xml")) {
        cerr << "Error loading haarcascade" << endl;
        exit(0);
    }

    if(!palm_cascade.load("../projet-bdm-asteroides/res/open_frontal_palm.xml")) {
        cerr << "Error loading haarcascade" << endl;
        exit(0);
    }


    timer = new QTimer(this);
    chrono=new QElapsedTimer();
    chrono->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(displayWebcam()));
    connect(timer,SIGNAL(timeout()),this,SLOT(displayTimer()));
    timer->start(100);

    connect(this, SIGNAL(asteroidsChange(int)), ui->glWidget, SLOT(asteroidsChange(int)));
    connect(ui->glWidget, SIGNAL(endOfGame(bool)), this, SLOT(openEndOfGameDialog(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chrono;
    delete timer;
    delete webcamFrame;
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
    Mat frame, frame_gray;
    vector<Rect> fists, palms;

    cap >> frame; // get frame
    flip(frame, frame, 1); // mirror effect
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY); // convert to gray

    Point p1(0,360), p2(1280, 360), p3(640, 0) , p4(640, 720);
    line(frame, p1, p2, Scalar(128,128,128), 2);
    line(frame, p3, p4, Scalar(128,128,128), 2);
    Point p5(440,260), p6(840,460);
    //rectangle(frame,p5, p6,Scalar(255,0,0),2);
    Point p7(0,280), p8(1280,280), p9(0,440), p10(1280,440);
    line(frame, p7, p8, Scalar(180,180,180), 2);
    line(frame, p9, p10, Scalar(180,180,180), 2);

    //-- Detect fists
    hand_cascade.detectMultiScale( frame_gray, fists, 1.1, 4, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );
    palm_cascade.detectMultiScale( frame_gray, palms, 1.1, 4, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );
    if (fists.size()==2)
    {
        // Draw green rectangle
        for (int i=0;i<(int)fists.size();i++){
            rectangle(frame,fists[i],Scalar(0,255,0),2);
        }

        if(fists[0].x< 640/2 && fists[0].y>480/2 && fists[1].x>640/2 && fists[1].y<480/2){
            qDebug()<<"gauche";
            ui->glWidget->computeMovement(1);
        }else if(fists[0].x< 640/2 && fists[0].y<480/2 && fists[1].x>640/2 && fists[1].y>480/2){
            qDebug()<<"droite";
            ui->glWidget->computeMovement(0);
        }
        else if(fists[0].y<480/2 && fists[1].y<480/2){
            qDebug()<<"haut";
            ui->glWidget->computeMovement(4);
        }else if(fists[0].y> 480/2 + 120 && fists[1].y>480/2 + 120){
            qDebug()<<"bas";
            ui->glWidget->computeMovement(5);
        }else if(fists[0].y>480/2 && fists[0].y<480/2+120 && fists[1].y>480/2 && fists[1].y<480/2+120){
            qDebug()<<"neutre";
            //ui->glWidget->computeMovement(5);
        }
    } else if(palms.size()==2){
        for (int i=0;i<(int)palms.size();i++){
            rectangle(frame,palms[i],Scalar(0,255,255),2);
        }
        if(260<palms[0].y && palms[0].y<460 && 260<palms[1].y && palms[1].y<460){
            qDebug()<<"avancer";
            ui->glWidget->computeMovement(2);
        }
    }


    // display in frame
    Mat frameToDisplay;
    frame.copyTo(frameToDisplay);
    QImage qImage(frameToDisplay.data, frameToDisplay.cols, frameToDisplay.rows, frameToDisplay.step, QImage::Format_BGR888);
    QPixmap qPix=QPixmap::fromImage(qImage);
    ui->camera->setPixmap(qPix.scaled(width/2, height/2, Qt::KeepAspectRatio));
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
