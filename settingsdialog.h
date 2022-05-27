#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(int number, QWidget *parent = nullptr);
    ~SettingsDialog();
    int getNewValue(){return newValue;};

private slots:
    void on_applyButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::SettingsDialog *ui;
    int newValue;
};

#endif // SETTINGSDIALOG_H
