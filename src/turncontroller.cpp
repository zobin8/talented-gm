#include "turncontroller.h"
#include "turnnotescontroller.h"
#include "turnloccontroller.h"
#include "turninitcontroller.h"
#include "turninfocontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QPushButton>

TurnController::TurnController(QObject *parent) : Controller(parent)
{

}

TurnController::~TurnController()
{

}

void TurnController::setWidgets(QLabel* turnCount, QPushButton* turnDeleteButton)
{
    uiTurnCount = turnCount;
    uiDelete = turnDeleteButton;

    view.append(uiTurnCount);
    updateDeleteButton();
}

void TurnController::updateDeleteButton()
{
    int turn = TalentData::getTalentFile()->getTurns().count();

    uiDelete->setEnabled(turn > 1);
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

    updateDeleteButton();
}

void TurnController::deleteTurn()
{
    QMessageBox msgBox;
    msgBox.setModal(true);
    msgBox.setText("Delete turn");
    msgBox.setInformativeText("Are you sure you want to delete this turn?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes)
    {
        emit updateModel(ConFreq::turn);

        TalentData::lockTalentFile()->deleteTurn();
        TalentData::unlockTalentFile();

        emit updateView(ConFreq::turn);
        emit updateView(ConFreq::hash);
    }

    updateDeleteButton();
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
