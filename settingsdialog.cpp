#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(int number, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->horizontalSlider->setValue(number);
    ui->valueLabel->setText(QString::number(ui->horizontalSlider->value())); // display default value
    ui->applyButton->setEnabled(false);

    connect(ui->horizontalSlider, &QSlider::valueChanged, this, [=] () {
        ui->applyButton->setEnabled(true);
        ui->valueLabel->setText(QString::number(ui->horizontalSlider->value()));
        newValue=ui->horizontalSlider->value();
    });
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_applyButton_clicked()
{
    accept();
}


void SettingsDialog::on_cancelButton_clicked()
{
    reject();
}
