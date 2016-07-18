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
    graphAlimento_ = new PlotGraph(plot1W, plot1H,bacSystem_->getAlimento0(), 40,"ALIMENTO");
    ui->plotAlimento->setScene(graphAlimento_);

    qreal plot2W = ui->plotReagente->width();
    qreal plot2H = ui->plotReagente->height();
    graphReagente_ = new PlotGraph(plot2W, plot2H,bacSystem_->getReagente0(), 40, "REAGENTE");
    ui->plotReagente->setScene(graphReagente_);

    qreal plot3W = ui->plotMetabolito->width();
    qreal plot3H = ui->plotMetabolito->height();
    graphMetabolito_ = new PlotGraph(plot3W, plot3H,bacSystem_->getMetabolito0(), 5, "METABOLITO");
    ui->plotMetabolito->setScene(graphMetabolito_);

    qreal plot4W = ui->plotResiduo->width();
    qreal plot4H = ui->plotResiduo->height();
    graphResiduo_ = new PlotGraph(plot4W, plot4H,bacSystem_->getResiduo0(), 1, "RESIDUO");
    ui->plotResiduo->setScene(graphResiduo_);

}

MainControl::~MainControl()
{
    delete ui;
}

void MainControl::on_startButton_clicked()
{
    timerId = startTimer(1000 / 20);
}

void MainControl::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    bacSystem_->propagate();
    std::vector<bool> alive = bacSystem_->getBacteriaAlive();

    bacta_->bacteriaUpdate(alive);

    graphAlimento_->updatePoint(bacSystem_->getAlimento0());
    graphReagente_->updatePoint(bacSystem_->getReagente0());
    graphMetabolito_->updatePoint(bacSystem_->getMetabolito0());
    graphResiduo_->updatePoint(bacSystem_->getResiduo0());
}
