#include "controller.h"

Controller::Controller(QObject* parent) : QObject(parent)
{

}

void Controller::setUi(Ui::MainWindow* anUi)
{
    ui = anUi;
}
