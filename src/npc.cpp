#include "npc.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "hitarea.h"
#include "svp.h"
#include "skill.h"

NPC::NPC()
{
    name = "Unnamed NPC";
    description = "";

    hitAreas = new QVector<HitArea>();
    skills = new QVector<Skill>();

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
    skills = new QVector<Skill>(*old->getSkills());

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
    skills = new QVector<Skill>();
    foreach (Skill skill, *npcTemp->getSkills())
    {
        Skill s = Skill(skill);
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

void NPC::setSkills(QVector<Skill>* s)
{
    delete skills;
    skills = new QVector<Skill>(*s);
}

QVector<Skill>* NPC::getSkills() const
{
    return skills;
}

int NPC::getSkillDice(Skill s) const
{
    int stat = getStatFromName(s.getStatName());
    int skill = s.getValue();
    return stat + skill;
}

int NPC::getStatFromName(QString n) const
{
    if (n == "Body ") return body;
    else if (n == "Coord") return coord;
    else if (n == "Sense") return sense;
    else if (n == "Mind ") return mind;
    else if (n == "Charm") return charm;
    else if (n == "Comm ") return comm;
    else return 0;
}

QDataStream& operator <<(QDataStream& out, const NPC& npc)
{
    out << QString("NPC5");

    out << npc.getName();
    out << npc.body;
    out << npc.coord;
    out << npc.sense;
    out << npc.mind;
    out << npc.charm;
    out << npc.comm;

    out << *npc.getHitAreas();

    out << npc.getDescription();

    out << *npc.getSkills();

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
    if (v == 3)
    {
        QVector<SVP> oldSkills = QVector<SVP>();
        in >> oldSkills;

        QVector<Skill>* skills = new QVector<Skill>();
        foreach (SVP svp, oldSkills)
        {
            Skill s = Skill(svp);
            skills->append(s);
        }
        npc.setSkills(skills);
    }
    if (v >= 4)
    {
        QString description;
        in >> description;
        npc.setDescription(description);
    }
    if (v >= 5)
    {
        QVector<Skill>* skills = new QVector<Skill>();
        in >> *skills;
        npc.setSkills(skills);
    }

    return in;
}
