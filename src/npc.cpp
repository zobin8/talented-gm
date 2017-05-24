#include "npc.h"
#include "npctemplate.h"
#include "talentdata.h"

NPC::NPC()
{
    name = "Unnamed NPC";

    body = 2;
    coord = 2;
    sense = 2;
    mind = 2;
    charm = 2;
    comm = 2;
}

NPC::NPC(NPC* old)
{
    setName(old->getName());

    body = old->body;
    coord = old->coord;
    sense = old->sense;
    mind = old->mind;
    charm = old->charm;
    comm = old->comm;
}

NPC::NPC(NPCTemplate* npcTemp)
{
    setName(npcTemp->getName());

    body = npcTemp->body;
    coord = npcTemp->coord;
    sense = npcTemp->sense;
    mind = npcTemp->mind;
    charm = npcTemp->charm;
    comm = npcTemp->comm;
}

NPC::~NPC()
{

}

void NPC::setName(QString aName)
{
    name = aName;
}

QString NPC::getName() const
{
    return name;
}

QDataStream& operator <<(QDataStream& out, const NPC& npc)
{
    out << QString("NPC1");

    out << npc.getName();
    out << npc.body;
    out << npc.coord;
    out << npc.sense;
    out << npc.mind;
    out << npc.charm;
    out << npc.comm;

    return out;
}

QDataStream& operator >>(QDataStream& in, NPC& npc)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "NPC");

    if (v >= 1)
    {
        QString name;
        in >> name;
        npc.setName(name);

        int body;
        in >> body;
        npc.body = body;

        int coord;
        in >> coord;
        npc.coord = coord;

        double sense;
        in >> sense;
        npc.sense = sense;

        int mind;
        in >> mind;
        npc.mind = mind;

        int charm;
        in >> charm;
        npc.charm = charm;

        int comm;
        in >> comm;
        npc.comm = comm;
    }

    return in;
}
