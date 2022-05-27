#include "endgamedialog.h"
#include "ui_endgamedialog.h"

EndGameDialog::EndGameDialog(QString title, QString message, QString score, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndGameDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->title->setText(title);
    ui->message->setText(message);
    ui->score->setText(score);
    setWindowTitle(title);

}

EndGameDialog::~EndGameDialog()
{
    delete ui;
}


/**
 * slot when quit button is clicked
 * @brief EndGameDialog::on_pushButton_clicked
 */
void EndGameDialog::on_pushButton_clicked()
{
    accept();
}

