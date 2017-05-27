#include "npcmenumodule.h"
#include "npc.h"
#include "hitmodule.h"
#include "hitarea.h"
#include "controller.h"
#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>
#include <QPushButton>

NPCMenuModule::NPCMenuModule()
{
    nameLabel = new QLabel();
    nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    hitContents = new QWidget();
    QVBoxLayout* hitLayout1 = new QVBoxLayout(hitContents);
    hitLayout1->setAlignment(Qt::AlignTop);

    mainContents = new QWidget();
    QVBoxLayout* hitLayout2 = new QVBoxLayout(mainContents);
    hitLayout2->setAlignment(Qt::AlignTop);

    npc = new NPC();
}

NPCMenuModule::~NPCMenuModule()
{
    mainContents->layout()->removeWidget(del);

    delete hitContents->layout();
    delete hitContents;
    delete mainContents->layout();
    delete nameLabel;
    //TODO: memory leak
    //delete mainContents;
    delete npc;
}

void NPCMenuModule::addWidgets()
{
    mainContents->layout()->addWidget(nameLabel);
    mainContents->layout()->addWidget(del);
    layout->addWidget(mainContents);
    layout->addWidget(hitContents);
}

NPC* NPCMenuModule::getNPC()
{
    QVector<HitArea>* areas = new QVector<HitArea>();
    QLayout* hitLayout = hitContents->layout();

    for (int i = 0; i < hitLayout->count(); i++)
    {
        QWidget* w = hitLayout->itemAt(i)->widget();
        HitModule* hitMod = dynamic_cast<HitModule*>(w);
        if (hitMod)
        {
            HitArea a = hitMod->getHitArea();
            areas->append(a);
        }
    }

    npc->setHitAreas(areas);

    return npc;
}

void NPCMenuModule::setNPC(NPC* newNPC)
{
    if (npc) delete npc;
    npc = new NPC(newNPC);

    nameLabel->setText(npc->getName());
    setDeleteText("Remove");
    setIdentifier(npc->getName());

    foreach (HitArea area, *npc->getHitAreas())
    {
        HitModule* hitMod = new HitModule();
        hitMod->setHitArea(area);
        hitMod->setSortID(area.getName());

        Controller::appendToLayout(hitMod, hitContents->layout());
    }
}
