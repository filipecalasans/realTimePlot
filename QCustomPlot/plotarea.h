#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QWidget>

namespace Ui {
class PlotArea;
}

class PlotArea : public QWidget
{
    Q_OBJECT

public:
    explicit PlotArea(QWidget *parent = 0);
    ~PlotArea();

private:
    Ui::PlotArea *ui;
};

#endif // PLOTAREA_H
