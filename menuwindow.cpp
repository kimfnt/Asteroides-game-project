#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "settingsdialog.h"
#include "mainwindow.h"
#include <QDebug>

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    // window not resizable
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_playButton_clicked()
{
    gameWindow = new MainWindow();
    emit gameWindow->asteroidsChange(numberAsteroids);

    connect(gameWindow, &MainWindow::openMenuWindow, this, &MenuWindow::show);

    gameWindow->setWindowState(Qt::WindowMaximized);
    gameWindow->show();
    this->hide();
}


void MenuWindow::on_settingsButton_clicked()
{
    SettingsDialog dialog(numberAsteroids, this);
    int code=dialog.exec();

    // Si on a clique sur ok, alors on modifie le nombre d'asteroides a afficher
    if (code==QDialog::Accepted){
        numberAsteroids=dialog.getNewValue();
    }
}

