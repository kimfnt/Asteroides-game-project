#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class EndGameDialog;
}

class EndGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndGameDialog(QString title, QString message, QString score, QWidget *parent = nullptr);
    ~EndGameDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EndGameDialog *ui;
};

#endif // ENDGAMEDIALOG_H
