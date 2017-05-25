#include "turncontroller.h"
#include "turnnotescontroller.h"
#include "turnloccontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QLabel>
#include <QList>

TurnController::TurnController(QObject *parent) : Controller(parent)
{
    turnNotesController = new TurnNotesController();
    turnLocController = new TurnLocController();

    turnControllers = QList<Controller*>();
    turnControllers.append(turnNotesController);
    turnControllers.append(turnLocController);

}

TurnController::~TurnController()
{
    foreach (Controller* con, turnControllers)
    {
        delete con;
    }
}

void TurnController::setWidgets(QLabel* turnCount)
{
    uiTurnCount = turnCount;
}

void TurnController::toView()
{
    foreach (Controller* con, turnControllers)
    {
        con->toView();
    }

    int count = TalentData::getTalentFile()->currentTurnIndex();
    QString counter = "Turn: " + QString::number(count + 1);
    uiTurnCount->setText(counter);
}

void TurnController::toModel()
{
    foreach (Controller* con, turnControllers)
    {
        con->toModel();
    }

    emit unsavedChange();
}

void TurnController::fromModel()
{
    foreach (Controller* con, turnControllers)
    {
        con->fromModel();
    }
}

void TurnController::fromView()
{
    foreach (Controller* con, turnControllers)
    {
        con->fromView();
    }
}

void TurnController::addTurn()
{
    fromView();
    toModel();
    TalentData::getTalentFile()->addTurn();
    fromModel();
    toView();
}

void TurnController::deleteTurn()
{
    fromView();
    toModel();

    TalentData::getTalentFile()->deleteTurn();

    fromModel();
    toView();
}

void TurnController::nextTurn()
{
    fromView();
    toModel();

    TalentData::getTalentFile()->nextTurn();

    fromModel();
    toView();
}

void TurnController::prevTurn()
{
    fromView();
    toModel();

    TalentData::getTalentFile()->previousTurn();

    fromModel();
    toView();
}
