#include "controller.h"

Controller::Controller(QObject* parent) : QObject(parent)
{

}

void Controller::on_update()
{
    fromModel();
    toView();
}
