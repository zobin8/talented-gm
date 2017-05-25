#include "npcmenumodule.h"
#include "npc.h"
#include <QLabel>
#include <QLayout>
#include <QPushButton>

NPCMenuModule::NPCMenuModule()
{
    nameLabel = new QLabel();
    nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    npc = new NPC();
}

NPCMenuModule::~NPCMenuModule()
{
    delete nameLabel;
}

void NPCMenuModule::addWidgets()
{
    layout->addWidget(nameLabel);
    layout->addWidget(getDeleteButton());
}

NPC* NPCMenuModule::getNPC()
{
    return npc;
}

void NPCMenuModule::setNPC(NPC* newNPC)
{
    if (npc) delete npc;
    npc = new NPC(newNPC);

    nameLabel->setText(npc->getName());
    setDeleteText("Remove");
    setIdentifier(npc->getName());
}
