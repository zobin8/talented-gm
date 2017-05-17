#include "controller.h"
//This might be needed:
//#include "talentdata.h"

Controller::Controller(QObject* parent, QMainWindow* aUi) : QObject(parent)
{
    ui = aUi;
}

void Controller::setData(TalentData * aData)
{
    data = aData;
    this->draw();
}
