#include "plotarea.h"
#include "ui_plotarea.h"

PlotArea::PlotArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotArea)
{
    ui->setupUi(this);
}

PlotArea::~PlotArea()
{
    delete ui;
}
