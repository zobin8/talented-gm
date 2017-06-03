#include "turninitcontroller.h"
#include "initiativeact.h"
#include "initmodule.h"
#include "talentdata.h"
#include "talentfile.h"
#include "turn.h"
#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QDoubleSpinBox>

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
        iMod->setSortID(QString::number(act.getPlayer().getValue()));

        connect(iMod, SIGNAL(viewUpdate()), this, SLOT(on_viewUpdate()));

        Controller::appendToLayout(iMod, initLayout);
    }
}

void TurnInitController::toModel()
{
    QVector<InitiativeAct>* modelInit = new QVector<InitiativeAct>(*initiative);
    TalentData::lockTalentFile()->currentTurn()->setInitiative(modelInit);
    TalentData::unlockTalentFile();
}

void TurnInitController::fromModel()
{
    const QVector<InitiativeAct>* modelInit = TalentData::lockTalentFile()->currentTurn()->getInitiative();
    initiative = new QVector<InitiativeAct>(*modelInit);

    TalentData::unlockTalentFile();
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
        if (identity == act.getPlayer().getString())
        {
            initiative->remove(i);
            break;
        }
    }

    tryToView();
    tryToModel();
}
