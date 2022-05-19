#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
  void on_playButton_clicked();
  void on_settingsButton_clicked();

private:
    Ui::MenuWindow *ui;
    int numberAsteroids=16;
    MainWindow *gameWindow=nullptr;
};
#endif // MENUWINDOW_H
