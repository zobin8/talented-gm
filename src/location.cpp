#include "location.h"
#include "npc.h"
#include "talentdata.h"
#include "talentfile.h"
#include "loctemplate.h"

Location::Location()
{
    npcs = QLinkedList<NPC*>();
    name = "No location loaded";

    minions1 = 0;
    minions2 = 0;
}

Location::Location(const Location* old)
{
    name = old->getName();
    minions1 = old->minions1;
    minions2 = old->minions2;
    npcs = QLinkedList<NPC*>(old->getNPCs());
}

Location::Location(const LocTemplate* locTemp)
{
    name = locTemp->getName();
    minions1 = locTemp->minions1;
    minions2 = locTemp->minions2;

    npcs = QLinkedList<NPC*>();
    foreach (NPCTemplate* npcTemp, locTemp->getNPCs())
    {
        NPC* npc = new NPC(npcTemp);
        npcs.append(npc);
    }
}

Location::~Location()
{
    foreach (NPC* npc, npcs)
    {
        delete npc;
    }
}

const QLinkedList<NPC*>& Location::getNPCs() const
{
    return npcs;
}

QLinkedList<NPC*>& Location::NPCs()
{
    return npcs;
}

QString Location::getName() const
{
    return name;
}

void Location::setName(QString aName)
{
    name = aName;
}

void Location::addNPC(NPC* npc)
{
    npcs.append(npc);
}

void Location::removeNPC(NPC* npc)
{
    npcs.removeOne(npc);
}

QDataStream& operator <<(QDataStream& out, const Location& loc)
{
    out << QString("Location1");

    out << loc.getName();
    out << loc.minions1;
    out << loc.minions2;

    return out;
}

QDataStream& operator >>(QDataStream& in, Location& loc)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "Location");

    if (v >= 1)
    {
        QString name;
        in >> name;
        loc.setName(name);

        in >> loc.minions1;
        in >> loc.minions2;
    }

    return in;
}
