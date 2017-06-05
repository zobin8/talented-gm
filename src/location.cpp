#include "location.h"
#include "npc.h"
#include "talentdata.h"
#include "talentfile.h"
#include "loctemplate.h"

Location::Location()
{
    tempNames = QMap<QString, int>();
    npcs = QLinkedList<NPC*>();
    name = "No location loaded";
    description = "";

    minions1 = 0;
    minions2 = 0;
    turn = 1;
}

Location::Location(const Location* old)
{
    tempNames = QMap<QString, int>(old->getTempNames());
    name = old->getName();
    minions1 = old->minions1;
    minions2 = old->minions2;
    description = old->getDescription();

    npcs = QLinkedList<NPC*>();
    foreach (const NPC* oldNPC, old->getNPCs())
    {
        NPC* newNPC = new NPC(oldNPC);
        addNPC(newNPC);
    }

    turn = old->getTurn();
}

Location::Location(const LocTemplate* locTemp)
{
    tempNames = QMap<QString, int>();
    name = locTemp->getName();
    minions1 = locTemp->minions1;
    minions2 = locTemp->minions2;
    description = locTemp->getDescription();

    npcs = QLinkedList<NPC*>();
    foreach (QString name, locTemp->getNPCs())
    {
        const NPCTemplate* npcTemp = TalentData::getTalentFile()->constNPCFromName(name);

        if (npcTemp)
        {
            NPC* npc = new NPC(npcTemp);
            incrementName(npc);
            npcs.append(npc);
        }
    }

    turn = 1;
}

Location::~Location()
{
    foreach (NPC* npc, npcs)
    {
        delete npc;
    }
}

QMap<QString, int> Location::getTempNames() const
{
    return tempNames;
}

void Location::incrementName(NPC* npc)
{
    int i = ++tempNames[npc->getName()];
    QString name = npc->getName() + " (" + QString::number(i) + ")";
    npc->setName(name);
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

QString Location::getDisplayName() const
{
    QString out = name + " (Turn " + QString::number(turn) + ")";
    return out;
}

void Location::setName(QString aName)
{
    name = aName;
}

QString Location::getDescription() const
{
    return description;
}

void Location::setDescription(QString aDesc)
{
    description = aDesc;
}

void Location::addNPC(NPC* npc)
{
    npcs.append(npc);
}

void Location::removeNPC(NPC* npc)
{
    npcs.removeOne(npc);
    delete npc;
}

void Location::setTurn(int i)
{
    turn = i;
}

void Location::incTurn()
{
    turn++;
}

int Location::getTurn() const
{
    return turn;
}

QDataStream& operator <<(QDataStream& out, const Location& loc)
{
    out << QString("Location4");

    out << loc.getName();
    out << loc.minions1;
    out << loc.minions2;

    out << loc.getNPCs().count();
    foreach (const NPC* npc, loc.getNPCs())
    {
        out << *npc;
    }

    out << loc.getTurn();

    out << loc.getDescription();

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

        int count;
        in >> count;
        loc.NPCs().clear();
        for (int i = 0; i < count; i++)
        {
            NPC* npc = new NPC();
            in >> *npc;
            loc.addNPC(npc);
        }
    }
    //I have no idea what happened to 2.
    if (v >= 3)
    {
        int turn;
        in >> turn;
        loc.setTurn(turn);
    }
    if (v >= 4)
    {
        QString description;
        in >> description;
        loc.setDescription(description);
    }

    return in;
}
