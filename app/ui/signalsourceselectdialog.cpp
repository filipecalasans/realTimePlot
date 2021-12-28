#include "signalsourceselectdialog.h"
#include "ui_signalsourceselectdialog.h"

SignalSourceSelectDialog::SignalSourceSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignalSourceSelectDialog)
{
    ui->setupUi(this);
}

SignalSourceSelectDialog::~SignalSourceSelectDialog()
{
    delete ui;
}
