#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QMainWindow>

#include "bacteriaanimation.h"
#include "BacteriaSystem.h"
#include "PlotGraph.h"

namespace Ui {
class MainControl;
}

class MainControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainControl(QWidget *parent = 0);
    ~MainControl();

private:
    Ui::MainControl *ui;
    int timerId;
    void timerEvent(QTimerEvent *event);

    bacteriaanimation * bacta_;
    BacteriaSystem * bacSystem_;
    PlotGraph * graphAlimento_;

};

#endif // MAINCONTROL_H
