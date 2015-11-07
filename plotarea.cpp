#include "plotarea.h"
#include "ui_plotarea.h"

PlotArea::PlotArea(QWidget *parent) :
    QCustomPlot(parent),
    ui(new Ui::PlotArea)
{
    ui->setupUi(this);

    plotLayout()->clear();

    QCPAxisRect *wideAxisRect = new QCPAxisRect(this);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->removeAxis(wideAxisRect->axis(QCPAxis::atRight));
    wideAxisRect->removeAxis(wideAxisRect->axis(QCPAxis::atTop));
    plotLayout()->addElement(0, 0, wideAxisRect);
}

PlotArea::~PlotArea()
{
    delete ui;
}




