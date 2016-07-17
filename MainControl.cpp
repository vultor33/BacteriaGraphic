#include "MainControl.h"
#include "ui_maincontrol.h"

#include <QDebug>

#include "bacteriaanimation.h"
#include "BacteriaSystem.h"

MainControl::MainControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainControl)
{
    ui->setupUi(this);
    qreal animW = ui->animation->width();
    qreal animH = ui->animation->height();
    bacta_ = new bacteriaanimation(animW, animH);
    ui->animation->setScene(bacta_);

    bacSystem_ = new BacteriaSystem;
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
    qDebug() << "alive:  " << alive[0] << " size:  " << alive.size();
    bacta_->bacteriaUpdate(alive);
    qDebug() << "passou ";

    //qDebug() << "Timer ID:" << event->timerId();

}
