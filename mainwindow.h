#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include <QElapsedTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);

signals:
    void openMenuWindow();
    void asteroidsChange(int);

private slots:
    void displayWebcam();
    void displayTimer();
    void on_quitButton_clicked();
    void openEndOfGameDialog(bool);

private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    cv::CascadeClassifier hand_cascade;
    cv::CascadeClassifier palm_cascade;
    QLabel * webcamFrame=nullptr;
    QElapsedTimer *chrono;
    QTimer *timer;
    QString time;
    int minutes=0;
    int height;
    int width;
};

#endif // MAINWINDOW_H
