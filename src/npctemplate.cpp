#include "npctemplate.h"
#include "svp.h"
#include "talentdata.h"
#include <QLinkedList>

NPCTemplate::NPCTemplate()
{
    name = NPCTemplate::randName();
    description = "";

    hitBoxes = new QLinkedList<SVP>();
    skills = new QLinkedList<SVP>();

    body = 2;
    coord = 2;
    sense = 2;
    mind = 2;
    charm = 2;
    comm = 2;
}

NPCTemplate::NPCTemplate(const NPCTemplate* old)
{
    setName(old->getName());
    setDescription(old->getDescription());

    hitBoxes = new QLinkedList<SVP>(*old->getHitBoxes());
    skills = new QLinkedList<SVP>(*old->getSkills());

    body = old->body;
    coord = old->coord;
    sense = old->sense;
    mind = old->mind;
    charm = old->charm;
    comm = old->comm;
}

NPCTemplate::~NPCTemplate()
{
    delete skills;
    delete hitBoxes;
}

void NPCTemplate::setName(QString aName)
{
    name = aName;
}

QString NPCTemplate::getName() const
{
    return name;
}

void NPCTemplate::setDescription(QString aDesc)
{
    description = aDesc;
}

QString NPCTemplate::getDescription() const
{
    return description;
}

QLinkedList<SVP>* NPCTemplate::getSkills() const
{
    return skills;
}

QLinkedList<SVP>* NPCTemplate::getHitBoxes() const
{
    return hitBoxes;
}

void NPCTemplate::addSkill(SVP svp)
{
    skills->append(svp);
}

void NPCTemplate::addHitBox(SVP svp)
{
    hitBoxes->append(svp);
}

void NPCTemplate::setSkills(QLinkedList<SVP>* s)
{
    delete skills;
    skills = s;
}

void NPCTemplate::setHitBoxes(QLinkedList<SVP>* h)
{
    delete hitBoxes;
    hitBoxes = h;
}

QString NPCTemplate::randName()
{
    return "Custom NPC #" + QString::number(qrand() % 1000000);
}

QDataStream& operator <<(QDataStream& out, const NPCTemplate& npc)
{
    out << QString("NPCTemplate2");

    out << npc.getName();
    out << npc.body;
    out << npc.coord;
    out << npc.sense;
    out << npc.mind;
    out << npc.charm;
    out << npc.comm;
    out << *npc.getSkills();
    out << *npc.getHitBoxes();
    out << npc.getDescription();

    return out;
}

QDataStream& operator >>(QDataStream& in, NPCTemplate& npc)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "NPCTemplate");

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

        QLinkedList<SVP>* skills = new QLinkedList<SVP>();
        in >> *skills;
        npc.setSkills(skills);

        QLinkedList<SVP>* hitBoxes = new QLinkedList<SVP>();
        in >> *hitBoxes;
        npc.setHitBoxes(hitBoxes);
    }
    if (v >= 2)
    {
        QString description;
        in >> description;
        npc.setDescription(description);
    }

    return in;
}
