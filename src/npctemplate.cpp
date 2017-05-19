#include "npctemplate.h"
#include "stringvaluepair.h"
#include <QLinkedList>

NPCTemplate::NPCTemplate()
{
    name = randName();

    hitBoxes = new QLinkedList<SVP>();
    skills = new QLinkedList<SVP>();

    body = 2;
    coord = 2;
    sense = 2;
    mind = 2;
    charm = 2;
    comm = 2;
}

NPCTemplate::NPCTemplate(NPCTemplate* old)
{
    setName(old->getName());

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

QString NPCTemplate::getName()
{
    return name;
}

QLinkedList<SVP>* NPCTemplate::getSkills()
{
    return skills;
}

QLinkedList<SVP>* NPCTemplate::getHitBoxes()
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

QString NPCTemplate::randName()
{
    return "Custom NPC #" + QString::number(qrand() % 1000000);
}
