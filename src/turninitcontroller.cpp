#include "turninitcontroller.h"
#include "initiativeact.h"
#include "initmodule.h"
#include "talentdata.h"
#include "talentfile.h"
#include "turn.h"
#include <QWidget>
#include <QLayout>

TurnInitController::TurnInitController(QObject *parent) : Controller(parent)
{
    initiative = new QVector<InitiativeAct>();
}

TurnInitController::~TurnInitController()
{
    delete uiContents;
    delete initiative;
}

void TurnInitController::toView()
{
    QLayout* initLayout = uiContents->layout();
    Controller::clearLayout(initLayout);

    foreach(InitiativeAct act, *initiative)
    {
        InitModule* iMod = new InitModule();
        iMod->addWidgets();
        iMod->setInitiativeAct(act);
        initLayout->addWidget(iMod);
    }
}

void TurnInitController::toModel()
{
    QVector<InitiativeAct>* modelInit = new QVector<InitiativeAct>(*initiative);
    TalentData::getTalentFile()->currentTurn()->setInitiative(modelInit);
}

void TurnInitController::fromModel()
{
    const QVector<InitiativeAct>* modelInit = TalentData::getTalentFile()->currentTurn()->getInitiative();
    initiative = new QVector<InitiativeAct>(*modelInit);
}

void TurnInitController::fromView()
{
    initiative->clear();
    QLayout* initLayout = uiContents->layout();

    for (int i = 0; i < initLayout->count(); i++)
    {
        QWidget* w = initLayout->itemAt(i)->widget();
        InitModule* iMod = dynamic_cast<InitModule*>(w);
        if (iMod)
        {
            InitiativeAct act = iMod->getInitiativeAct();
            initiative->append(act);
        }
    }

}

void TurnInitController::setWidgets(QWidget* turnInitContents)
{
    uiContents = turnInitContents;
}

void TurnInitController::addPlayer()
{

}

void TurnInitController::deleteInit(QString identity)
{
    for (int i = 0; i < initiative->count(); i++)
    {
        InitiativeAct act = initiative->at(i);
        if (identity == act.getPlayer().string)
        {
            initiative->remove(i);
            break;
        }
    }

    toView();
    toModel();
}
