#include "npc.h"
#include "stringvaluepair.h"
#include <QLinkedList>

NPC::NPC()
{
    body = 2;
    coord = 2;
    sense = 2;
    mind = 2;
    charm = 2;
    comm = 2;
}

NPC::NPC(NPC* copy)
{
    name = copy->name;
    body = copy->body;
    coord = copy->coord;
    sense = copy->sense;
    mind = copy->mind;
    charm = copy->charm;
    comm = copy->comm;
}

NPC::~NPC()
{
    delete skills;
    delete hitBoxes;
}

void NPC::setName(QString aName)
{
    name = aName;
}

QString NPC::getName()
{
    return name;
}

QLinkedList<SVP>* NPC::getSkills()
{
    return skills;
}

QLinkedList<SVP>* NPC::getHitBoxes()
{
    return hitBoxes;
}

void NPC::addSkill(SVP svp)
{
    skills->append(svp);
}

void NPC::addHitBox(SVP svp)
{
    hitBoxes->append(svp);
}
