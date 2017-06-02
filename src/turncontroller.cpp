#include "turncontroller.h"
#include "turnnotescontroller.h"
#include "turnloccontroller.h"
#include "turninitcontroller.h"
#include "turninfocontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QLabel>
#include <QList>

TurnController::TurnController(QObject *parent) : Controller(parent)
{

}

TurnController::~TurnController()
{

}

void TurnController::setWidgets(QLabel* turnCount)
{
    uiTurnCount = turnCount;
}

void TurnController::toView()
{
    int count = TalentData::getTalentFile()->currentTurnIndex();
    QString counter = "Turn: " + QString::number(count + 1);
    uiTurnCount->setText(counter);
}

void TurnController::toModel()
{
    emit updateView(ConFreq::hash);
}

void TurnController::fromModel()
{

}

void TurnController::fromView()
{

}

void TurnController::addTurn()
{
    emit updateModel(ConFreq::turn);

    TalentData::getTalentFile()->addTurn();

    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
}

void TurnController::deleteTurn()
{
    emit updateModel(ConFreq::turn);

    TalentData::getTalentFile()->deleteTurn();

    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
}

void TurnController::nextTurn()
{
    emit updateModel(ConFreq::turn);

    TalentData::getTalentFile()->nextTurn();

    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
}

void TurnController::prevTurn()
{
    emit updateModel(ConFreq::turn);

    TalentData::getTalentFile()->previousTurn();

    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
}
