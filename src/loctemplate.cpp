#include "loctemplate.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "talentfile.h"

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
    npcs = QLinkedList<NPCTemplate*>(old->NPCs());
}

const QLinkedList<NPCTemplate*>& LocTemplate::getNPCs() const
{
    return npcs;
}

QLinkedList<NPCTemplate*>& LocTemplate::NPCs()
{
    return npcs;
}

QString LocTemplate::getName() const
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

QDataStream& operator <<(QDataStream& out, const LocTemplate& locTemp)
{
    out << QString("LocTemplate1");

    out << locTemp.getName();
    out << locTemp.minions1;
    out << locTemp.minions2;

    out << locTemp.getNPCs().count();
    foreach (NPCTemplate* npc, locTemp.getNPCs())
    {
        out << npc->getName();
    }

    return out;
}

QDataStream& operator >>(QDataStream& in, LocTemplate& locTemp)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "LocTemplate");

    if (v == 1)
    {
        QString name;
        in >> name;
        locTemp.setName(name);

        in >> locTemp.minions1;
        in >> locTemp.minions2;

        int count;
        in >> count;
        for (int i = 0; i < count; i++)
        {
            QString n;
            in >> n;
            NPCTemplate* npc = TalentData::getTalentFile()->getNPCFromName(n);
            if (npc)
            {
                locTemp.addNPC(npc);
            }
        }
    }

    return in;
}
