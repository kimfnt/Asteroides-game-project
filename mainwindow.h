#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include <QElapsedTimer>

//using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void openMenuWindow();
    void asteroidsChange(int);

private slots:
    void displayWebcam();
    void displayTimer();
    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    cv::CascadeClassifier hand_cascade;
    QLabel * webcamFrame=nullptr;
    QElapsedTimer *chrono;
    int minutes=0;
    int height;
    int width;
};

#endif // MAINWINDOW_H
