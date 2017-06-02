#include "turnloccontroller.h"
#include "location.h"
#include "talentdata.h"
#include "talentfile.h"
#include "turn.h"
#include "npcmenumodule.h"
#include "npc.h"
#include <QLabel>
#include <QSpinBox>
#include <QLayout>
#include <QTextEdit>

TurnLocController::TurnLocController(QObject *parent) : Controller(parent)
{
    loc = new Location();
}

TurnLocController::~TurnLocController()
{
    delete loc;
}

void TurnLocController::setWidgets(QSpinBox* turnMinionSpin1, QSpinBox* turnMinionSpin2, QLabel* turnLocName, QWidget* turnNPCContents, QTextEdit* turnLocDesc)
{
    uiMinions1 = turnMinionSpin1;
    uiMinions2 = turnMinionSpin2;
    uiLocName = turnLocName;
    uiContents = turnNPCContents;
    uiDesc = turnLocDesc;

    connect(uiMinions1, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
    connect(uiMinions2, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
}

void TurnLocController::toView()
{
    uiLocName->setText(loc->getDisplayName());
    uiDesc->setText(loc->getDescription());
    uiMinions1->setValue(loc->minions1);
    uiMinions2->setValue(loc->minions2);

    QLayout* lay = uiContents->layout();
    Controller::clearLayout(lay);

    foreach (NPC* npc, loc->getNPCs())
    {
        NPCMenuModule* npcMod = new NPCMenuModule();
        npcMod->addWidgets();
        npcMod->requireConfirmation();
        npcMod->setNPC(npc);
        npcMod->setSortID(npc->getName());

        Controller::appendToLayout(npcMod, uiContents->layout());

        connect(npcMod, SIGNAL(killMe(MenuModule*)), this, SLOT(on_deletionEvent(MenuModule*)));
        connect(npcMod, SIGNAL(viewNPC(NPC*)), this, SLOT(on_viewNPC(NPC*)));
        connect(npcMod, SIGNAL(viewUpdate()), this, SLOT(on_viewUpdate()));
    }
}

void TurnLocController::toModel()
{
    Location* modelLoc = new Location(loc);
    TalentData::getTalentFile()->currentTurn()->setLoc(modelLoc);

    emit updateView(ConFreq::hash);
}

void TurnLocController::fromModel()
{
    const Location* modelLoc = TalentData::getTalentFile()->currentTurn()->getLoc();
    delete loc;
    loc = new Location(modelLoc);
}

void TurnLocController::fromView()
{
    loc->minions1 = uiMinions1->value();
    loc->minions2 = uiMinions2->value();

    while (loc->getNPCs().count() > 0)
    {
        loc->removeNPC(loc->getNPCs().first());
    }

    QLayout* npcLayout = uiContents->layout();
    for (int i = 0; i < npcLayout->count(); i++)
    {
        QWidget* widget = npcLayout->itemAt(i)->widget();
        NPCMenuModule* npcMod = dynamic_cast<NPCMenuModule*>(widget);
        if (npcMod)
        {
            NPC* oldNPC = npcMod->getNPC();
            NPC* npc = new NPC(oldNPC);
            loc->addNPC(npc);
        }
    }
}

void TurnLocController::on_deletionEvent(MenuModule* toDelete)
{
    emit deletedNPC(toDelete->getIdentifier());

    uiContents->layout()->removeWidget(toDelete);
    delete toDelete;

    fromView();
    toModel();
}

void TurnLocController::on_viewNPC(NPC* npc)
{
    emit viewNPC(npc);
}
