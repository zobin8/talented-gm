#include "npcmenumodule.h"
#include "npc.h"
#include "hitmodule.h"
#include "hitarea.h"
#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>
#include <QPushButton>

NPCMenuModule::NPCMenuModule()
{
    nameLabel = new QLabel();
    nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    hitContents = new QWidget();
    QVBoxLayout* hitLayout = new QVBoxLayout(hitContents);
    hitLayout->setAlignment(Qt::AlignTop);

    npc = new NPC();
}

NPCMenuModule::~NPCMenuModule()
{
    delete hitContents->layout();
    delete hitContents;
    delete nameLabel;
    delete npc;
}

void NPCMenuModule::addWidgets()
{
    layout->addWidget(nameLabel);
    layout->addWidget(hitContents);
    layout->addWidget(getDeleteButton());
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
        hitContents->layout()->addWidget(hitMod);
    }
}
