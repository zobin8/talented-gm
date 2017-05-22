#include "loctemplate.h"
#include "npctemplate.h"

LocTemplate::LocTemplate()
{
    npcs = QLinkedList<NPCTemplate*>();
    name = LocTemplate::randName();

    minions1 = 0;
    minions2 = 0;
}

LocTemplate::LocTemplate(LocTemplate* old)
{
    name = old->getName();
    minions1 = old->minions1;
    minions2 = old->minions2;
    npcs = QLinkedList<NPCTemplate*>(old->getNPCs());
}

QLinkedList<NPCTemplate*>& LocTemplate::getNPCs()
{
    return npcs;
}

QString LocTemplate::getName()
{
    return name;
}

void LocTemplate::setName(QString aName)
{
    name = aName;
}

void LocTemplate::addNPC(NPCTemplate* npc)
{
    npcs.append(npc);
}

void LocTemplate::removeNPC(NPCTemplate* npc)
{
    npcs.removeOne(npc);
}

QString LocTemplate::randName()
{
    return "Custom Location #" + QString::number(qrand() % 1000000);
}
