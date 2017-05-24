#include "turncontroller.h"
#include "turnnotescontroller.h"
#include <QLabel>
#include <QList>

TurnController::TurnController(QObject *parent) : Controller(parent)
{
    turnControllers = QList<Controller*>();
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
}

void TurnController::toModel()
{
    foreach (Controller* con, turnControllers)
    {
        con->toModel();
    }
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
