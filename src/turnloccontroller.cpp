#include "turnloccontroller.h"
#include "location.h"
#include "talentdata.h"
#include "talentfile.h"
#include "turn.h"
#include <QLabel>
#include <QSpinBox>

TurnLocController::TurnLocController(QObject *parent) : Controller(parent)
{
    loc = new Location();
}

TurnLocController::~TurnLocController()
{
    delete loc;
}

void TurnLocController::setWidgets(QSpinBox* turnMinionSpin1, QSpinBox* turnMinionSpin2, QLabel* turnLocName)
{
    uiMinions1 = turnMinionSpin1;
    uiMinions2 = turnMinionSpin2;
    uiLocName = turnLocName;
}

void TurnLocController::toView()
{
    uiLocName->setText(loc->getName());
    uiMinions1->setValue(loc->minions1);
    uiMinions2->setValue(loc->minions2);
}

void TurnLocController::toModel()
{
    Location* modelLoc = new Location(loc);
    TalentData::getTalentFile()->currentTurn()->setLoc(modelLoc);
}

void TurnLocController::fromModel()
{
    const Location* modelLoc = TalentData::getTalentFile()->currentTurn()->getLoc();
    delete loc;
    loc = new Location(modelLoc);
}

void TurnLocController::fromView()
{
    loc->setName(uiLocName->text());
    loc->minions1 = uiMinions1->value();
    loc->minions2 = uiMinions2->value();
}
