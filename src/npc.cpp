#include "npc.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "hitarea.h"
#include "svp.h"

NPC::NPC()
{
    name = "Unnamed NPC";
    description = "";

    hitAreas = new QVector<HitArea>();
    skills = new QVector<SVP>();

    body = 2;
    coord = 2;
    sense = 2;
    mind = 2;
    charm = 2;
    comm = 2;
}

NPC::NPC(const NPC* old)
{
    setName(old->getName());
    setDescription(old->getDescription());

    hitAreas = new QVector<HitArea>(*old->getHitAreas());
    skills = new QVector<SVP>(*old->getSkills());

    body = old->body;
    coord = old->coord;
    sense = old->sense;
    mind = old->mind;
    charm = old->charm;
    comm = old->comm;
}

NPC::NPC(const NPCTemplate* npcTemp)
{
    setName(npcTemp->getName());
    setDescription(npcTemp->getDescription());

    hitAreas = new QVector<HitArea>();
    foreach (SVP svp, *npcTemp->getHitBoxes())
    {
        HitArea area = HitArea(svp);
        hitAreas->append(area);
    }
    skills = new QVector<SVP>();
    foreach (SVP svp, *npcTemp->getSkills())
    {
        SVP s = SVP(svp);
        skills->append(s);
    }

    body = npcTemp->body;
    coord = npcTemp->coord;
    sense = npcTemp->sense;
    mind = npcTemp->mind;
    charm = npcTemp->charm;
    comm = npcTemp->comm;
}

NPC::~NPC()
{
    delete hitAreas;
    delete skills;
}

void NPC::setName(QString aName)
{
    name = aName;
}

QString NPC::getName() const
{
    return name;
}

void NPC::setDescription(QString aDesc)
{
    description = aDesc;
}

QString NPC::getDescription() const
{
    return description;
}

void NPC::setHitAreas(QVector<HitArea>* areas)
{
    delete hitAreas;
    hitAreas = new QVector<HitArea>(*areas);
}

QVector<HitArea>* NPC::getHitAreas() const
{
    return hitAreas;
}

void NPC::setSkills(QVector<SVP>* s)
{
    delete skills;
    skills = new QVector<SVP>(*s);
}

QVector<SVP>* NPC::getSkills() const
{
    return skills;
}

int NPC::getStatFromName(QString n)
{
    if (n == "Body") return body;
    else if (n == "Coordination") return coord;
    else if (n == "Sense") return sense;
    else if (n == "Mind") return mind;
    else if (n == "Charm") return charm;
    else if (n == "Command") return comm;
    else return 0;
}

QDataStream& operator <<(QDataStream& out, const NPC& npc)
{
    out << QString("NPC4");

    out << npc.getName();
    out << npc.body;
    out << npc.coord;
    out << npc.sense;
    out << npc.mind;
    out << npc.charm;
    out << npc.comm;

    out << *npc.getHitAreas();
    out << *npc.getSkills();

    out << npc.getDescription();

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
    if (v >= 2)
    {
        QVector<HitArea>* areas = new QVector<HitArea>();
        in >> *areas;
        npc.setHitAreas(areas);
    }
    if (v >= 3)
    {
        QVector<SVP>* skills = new QVector<SVP>();
        in >> *skills;
        npc.setSkills(skills);
    }
    if (v >= 4)
    {
        QString description;
        in >> description;
        npc.setDescription(description);
    }

    return in;
}
