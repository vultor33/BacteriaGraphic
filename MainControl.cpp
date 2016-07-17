#include "MainControl.h"
#include "ui_maincontrol.h"

#include "bacteriaanimation.h"
#include "BacteriaSystem.h"

MainControl::MainControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainControl)
{
    ui->setupUi(this);
    qreal animW = ui->animation->width();
    qreal animH = ui->animation->height();
    bacta = new bacteriaanimation(animW, animH);
    ui->animation->setScene(bacta);

    BacteriaSystem bacSys;
    bacSys.propagate();
}

MainControl::~MainControl()
{
    delete ui;
}
