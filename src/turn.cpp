#include "turn.h"
#include "talentdata.h"
#include "talentfile.h"
#include "loctemplate.h"
#include "npctemplate.h"
#include "npc.h"
#include "location.h"
#include "initiativeact.h"
#include <QVector>

Turn::Turn()
{
    notes = "";
    loc = new Location();
    initiative = new QVector<InitiativeAct>();
}

Turn::Turn(Turn* old)
{
    notes = old->getNotes();
}

QString Turn::getNotes() const
{
    return notes;
}

void Turn::setNotes(QString aString)
{
    notes = aString;
}

void Turn::setLocTemplate(const LocTemplate* locTemp)
{
    delete loc;
    loc = new Location(locTemp);
}

void Turn::addNPCTemplate(const NPCTemplate* npcTemp)
{
    NPC* npc = new NPC(npcTemp);
    loc->addNPC(npc);
    loc->incrementName(npc);
    addNPCInitiative(npc);
}

const Location* Turn::getLoc() const
{
    return loc;
}

void Turn::setLoc(Location* aLoc)
{
    delete loc;
    loc = new Location(aLoc);
}

const QVector<InitiativeAct>* Turn::getInitiative() const
{
    return initiative;
}

void Turn::setInitiative(QVector<InitiativeAct>* init)
{
    delete initiative;
    initiative = new QVector<InitiativeAct>(*init);
}

void Turn::addNPCInitiative(NPC* npc)
{
    InitiativeAct act = InitiativeAct();
    SVP player = SVP(npc->getName(), npc->sense);
    act.setPlayer(player);
    initiative->append(act);
}

QDataStream& operator <<(QDataStream& out, const Turn& turn)
{
    out << QString("Turn3");

    out << turn.getNotes();
    out << *turn.getLoc();
    out << *turn.getInitiative();

    return out;
}

QDataStream& operator >>(QDataStream& in, Turn& turn)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "Turn");

    if (v >= 1)
    {
        QString notes;
        in >> notes;
        turn.setNotes(notes);
    }
    if (v >= 2)
    {
        Location* loc = new Location();
        in >> *loc;
        turn.setLoc(loc);
    }
    if (v >= 3)
    {
        QVector<InitiativeAct>* init = new QVector<InitiativeAct>();
        in >> *init;
        turn.setInitiative(init);
    }

    return in;
}
