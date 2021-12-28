#ifndef SIGNALSOURCESELECTDIALOG_H
#define SIGNALSOURCESELECTDIALOG_H

#include <QDialog>

namespace Ui {
class SignalSourceSelectDialog;
}

class SignalSourceSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignalSourceSelectDialog(QWidget *parent = nullptr);
    ~SignalSourceSelectDialog();

private:
    Ui::SignalSourceSelectDialog *ui;
};

#endif // SIGNALSOURCESELECTDIALOG_H
