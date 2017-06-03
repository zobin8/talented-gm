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

    view.append(uiTurnCount);
}

void TurnController::toView()
{
    int count = TalentData::lockTalentFile()->currentTurnIndex();
    TalentData::unlockTalentFile();

    QString counter = "Turn: " + QString::number(count + 1);
    uiTurnCount->setText(counter);
}

void TurnController::toModel()
{

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

    TalentData::lockTalentFile()->addTurn();
    TalentData::unlockTalentFile();

    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
}

void TurnController::deleteTurn()
{
    emit updateModel(ConFreq::turn);

    TalentData::lockTalentFile()->deleteTurn();
    TalentData::unlockTalentFile();

    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
}

void TurnController::nextTurn()
{
    emit updateModel(ConFreq::turn);

    TalentData::lockTalentFile()->nextTurn();
    TalentData::unlockTalentFile();

    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
}

void TurnController::prevTurn()
{
    emit updateModel(ConFreq::turn);

    TalentData::lockTalentFile()->previousTurn();
    TalentData::unlockTalentFile();

    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
}
