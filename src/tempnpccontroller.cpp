#include "tempnpccontroller.h"
#include "npctemplate.h"
#include "menumodule.h"
#include "talentdata.h"
#include <QLayout>
#include <QVBoxLayout>

TempNPCController::TempNPCController(QObject *parent) : Controller(parent)
{
    npcTemplates = QLinkedList<NPCTemplate*>();
}

void TempNPCController::setWidgets(QWidget* tempNPCContents)
{
    uiNPCContents = tempNPCContents;
}

void TempNPCController::toView()
{
    QLayout* lay = uiNPCContents->layout();
    Controller::clearLayout(lay);

    foreach (NPCTemplate* npc, npcTemplates)
    {
        MenuModule* npcMod = new MenuModule();
        npcMod->setDeleteText("Delete NPC: " + npc->getName());
        npcMod->setIdentifier(npc->getName());

        QVBoxLayout* npcLayout = static_cast<QVBoxLayout*>(uiNPCContents->layout());
        int i = npcLayout->count();
        npcLayout->insertWidget(i, npcMod);

        connect(npcMod, SIGNAL(killMe(MenuModule*)), this, SLOT(on_deletionEvent(MenuModule*)));
    }
}

void TempNPCController::fromModel()
{
    QLinkedList<NPCTemplate*> model = TalentData::getInstance().getNPCTemplates();
    npcTemplates = QLinkedList<NPCTemplate*>(model);
}

void TempNPCController::fromView()
{
    npcTemplates.clear();
    QLayout* npcLayout = uiNPCContents->layout();
    for (int i = 0; i < npcLayout->count(); i++)
    {
        QWidget* widget = npcLayout->itemAt(i)->widget();
        MenuModule* menuMod = dynamic_cast<MenuModule*>(widget);
        if (menuMod)
        {
            QString name = menuMod->getIdentifier();
            NPCTemplate* npc = TalentData::getInstance().getNPCFromName(name);

            if (npc)
            {
                npcTemplates.append(npc);
            }
        }
    }
}

void TempNPCController::toModel()
{
    TalentData::getInstance().setNPCTemplates(npcTemplates);

    emit update();
}

void TempNPCController::on_deletionEvent(MenuModule* menMod)
{
    uiNPCContents->layout()->removeWidget(menMod);
    delete menMod;

    fromView();
    toModel();
}