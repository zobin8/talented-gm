#include "locationtemplate.h"
#include "npctemplate.h"

LocationTemplate::LocationTemplate()
{
    npcs = QLinkedList<NPCTemplate*>();
    name = LocationTemplate::randName();

    minions1 = 0;
    minions2 = 0;
}

LocationTemplate::LocationTemplate(LocationTemplate* old)
{
    name = old->getName();
    minions1 = old->minions1;
    minions2 = old->minions2;
    npcs = QLinkedList<NPCTemplate*>(old->getNPCs());
}

QLinkedList<NPCTemplate*>& LocationTemplate::getNPCs()
{
    return npcs;
}

QString LocationTemplate::getName()
{
    return name;
}

void LocationTemplate::setName(QString aName)
{
    name = aName;
}

void LocationTemplate::addNPC(NPCTemplate* npc)
{
    npcs.append(npc);
}

void LocationTemplate::removeNPC(NPCTemplate* npc)
{
    npcs.removeOne(npc);
}

QString LocationTemplate::randName()
{
    return "Custom Location #" + QString::number(qrand() % 1000000);
}
