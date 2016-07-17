#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QMainWindow>

#include "bacteriaanimation.h"

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

    bacteriaanimation * bacta;


};

#endif // MAINCONTROL_H
