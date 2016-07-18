#include "MainControl.h"
#include "ui_maincontrol.h"

#include <QDebug>

#include "bacteriaanimation.h"
#include "BacteriaSystem.h"
#include "PlotGraph.h"

MainControl::MainControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainControl)
{
    bacSystem_ = new BacteriaSystem;

    ui->setupUi(this);
    qreal animW = ui->animation->width();
    qreal animH = ui->animation->height();
    bacta_ = new bacteriaanimation(animW, animH);
    ui->animation->setScene(bacta_);

    qreal plot1W = ui->plotAlimento->width();
    qreal plot1H = ui->plotAlimento->height();
    graphAlimento_ = new PlotGraph(plot1W, plot1H,bacSystem_->getAlimento0());
    ui->plotAlimento->setScene(graphAlimento_);

    timerId = startTimer(1000 / 1);
}

MainControl::~MainControl()
{
    delete ui;
}

void MainControl::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    bacSystem_->propagate();
    std::vector<bool> alive = bacSystem_->getBacteriaAlive();
    //qDebug() << "alive:  " << alive[0] << " size:  " << alive.size();
    bacta_->bacteriaUpdate(alive);
    //qDebug() << "passou ";
    graphAlimento_->updatePoint(bacSystem_->getAlimento0());

    //qDebug() << "Timer ID:" << event->timerId();

}
